#pragma once

#include <SFML/Audio.hpp>
#include "Timer.hpp"
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <memory>
#include <tuple>
#include <condition_variable>


namespace Veri {
	class AudioPlayer {
	public:
		AudioPlayer(bool repeat = false);
		~AudioPlayer();

		AudioPlayer(AudioPlayer const& other);
		AudioPlayer& operator=(AudioPlayer const& other);

		AudioPlayer(AudioPlayer&& other) noexcept;
		AudioPlayer& operator=(AudioPlayer&& other) noexcept;

		void AddSound(std::string const& filename, float volume = 1.f, Timer::Duration const& sleepTime = Timer::MilliSeconds(0));
		void Stop();
		void Restart();
	private:
		void Play();

	private:
		bool m_IsRepeat;

		sf::Sound m_Sound;
		sf::SoundBuffer m_SoundBuffer;
		std::deque<std::tuple<std::string, Timer::Duration, sf::Sound>> m_Queue;

		std::atomic<bool> m_IsPlaying;
		std::thread m_PlayThread;

		std::condition_variable m_QueueCondition;
	};
}