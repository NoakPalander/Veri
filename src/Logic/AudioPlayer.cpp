#include "AudioPlayer.hpp"
#include "Logger.hpp"
#include "fmt/fmt.hpp"
#include <thread>
#include "Event/EventManager.hpp"
#include "Event/KbEvent.hpp"
#include "Filesystem.hpp"
#include <queue>

namespace {
    std::mutex s_QueueMutex;
}

namespace Veri {
	AudioPlayer::AudioPlayer(bool repeat) 
		:	m_IsRepeat{repeat}, m_Sound{}, m_SoundBuffer{}, m_Queue{}, m_IsPlaying{true} 
	{
		m_PlayThread = std::thread(&AudioPlayer::Play, this);
	}


	AudioPlayer::AudioPlayer(AudioPlayer const& other) {
		if (&other != this) {
			m_IsRepeat 		 = other.m_IsRepeat;
			m_Sound			 = other.m_Sound;
			m_SoundBuffer    = other.m_SoundBuffer;
			m_Queue			 = other.m_Queue;
		}
	}


	AudioPlayer& AudioPlayer::operator=(AudioPlayer const& other) {
		if (&other != this) {
			m_IsRepeat 		 = other.m_IsRepeat;
			m_Sound			 = other.m_Sound;
			m_SoundBuffer    = other.m_SoundBuffer;
			m_Queue			 = other.m_Queue;
		}

		return *this;
	}


	AudioPlayer::AudioPlayer(AudioPlayer&& other) noexcept {
		if (&other != this) {
			m_IsRepeat 		 = std::move(other.m_IsRepeat);
			m_Sound			 = std::move(other.m_Sound);
			m_SoundBuffer    = std::move(other.m_SoundBuffer);
			m_Queue			 = std::move(other.m_Queue);
		}
	}


	AudioPlayer& AudioPlayer::operator=(AudioPlayer&& other) noexcept {
		if (&other != this) {
			m_IsRepeat 		 = std::move(other.m_IsRepeat);
			m_Sound			 = std::move(other.m_Sound);
			m_SoundBuffer    = std::move(other.m_SoundBuffer);
			m_Queue			 = std::move(other.m_Queue);
		}

		return *this;
	}


	AudioPlayer::~AudioPlayer() {
		Stop();
	}


	void AudioPlayer::AddSound(std::string const& filename, float volume, Timer::Duration const& sleepTime) {
		// Checks if the filename is valid
		if (!fs::exists(filename)) {
			if (!Logger::Debug(Logger::Level::Critical, fmt::format("Cannot find the file{}!", fs::path(filename).filename().string()), []{
				fmt::print("Aborted on [file] {} / [line] {}", __FILE__, __LINE__);
				std::abort();
			})) {
				Logger::Log(Logger::Level::Warn, fmt::format("Cannot find the soundfile {}!", filename));
			}
		}

		Logger::Debug(Logger::Level::Info, fmt::format("Adding sound {} to the queue!", fs::path(filename).filename().string()));
		
		// Appends a new sound to the queue
		sf::Sound sound{};
		sound.setVolume(volume);
		
		std::lock_guard<std::mutex> lock{s_QueueMutex};
		m_Queue.emplace_back(std::make_tuple(filename, sleepTime, std::move(sound)));	
		m_QueueCondition.notify_one();
	}


	void AudioPlayer::Stop() {
		m_IsPlaying = false;
		m_QueueCondition.notify_one();
		m_PlayThread.join();
	}


	void AudioPlayer::Restart() {
		Stop();
		Timer::Sleep(Timer::MilliSeconds(200));

		m_IsPlaying = true;
		m_PlayThread = std::thread(&AudioPlayer::Play, this);
	}


	void AudioPlayer::Play() {
		while (m_IsPlaying) {
			// Sleeps the current thread until the song queue isn't empty, or until the thread is terminated
			std::unique_lock<std::mutex> queueLock{s_QueueMutex};
			m_QueueCondition.wait(queueLock, [this](){ return !m_Queue.empty() || !m_IsPlaying; });
			queueLock.unlock();

			// Iterates the queue
			for (auto&[name, sleepTime, song] : m_Queue) {
				Timer::Sleep(sleepTime);

				// Loads the buffer
				m_SoundBuffer.loadFromFile(name);
				song.setBuffer(m_SoundBuffer);

				Logger::Debug(Logger::Level::Info, fmt::format("Playing sound {}!", fs::path(name).filename().string()));
				
				std::condition_variable songCond{};
				
				// Plays the song
				song.play();
				// Notifies the thread to stop sleeping when the song has finished playing
				std::thread waitChecker([&song, &songCond](){
					while(song.getStatus() == sf::Sound::Playing);
					songCond.notify_one();
				});

				waitChecker.detach();

				std::unique_lock<std::mutex> songLock{s_QueueMutex};
				songCond.wait(songLock);

				if (!m_IsRepeat) {
					Logger::Debug(Logger::Level::Info, fmt::format("Removing sound {} from the queue!", 
						fs::path(name).filename().string()));
					
					// Removes the sound from the queue
					m_Queue.pop_front();
				}

				songLock.unlock();
			}
		}
	}
}