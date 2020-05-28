#include "Logger.hpp"

#include "Validator.hpp"
#include "fmt/fmt.hpp"
#include "Filesystem.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace {
    std::shared_ptr<spdlog::logger> s_Logger;
    std::vector<std::pair<std::string, uint>> s_DebugHistory;
}

namespace Veri {
    void Logger::Init(std::string const& branch, std::string_view mode, std::string const& title) {
        spdlog::set_pattern("%^[%T] %n: %v%$"); 
        s_Logger = spdlog::stdout_color_mt(fmt::format("[b:{}, m:{}] - {}", branch, mode, title));
        s_Logger->set_level(spdlog::level::trace);
    }

    void Logger::Log(Level const& level, std::string_view message) {
        switch(level) {
            case Level::Trace:      s_Logger->trace(message);       break;
            case Level::Info:       s_Logger->info(message);        break;
            case Level::Warn:       s_Logger->warn(message);        break;
            case Level::Critical:   s_Logger->critical(message);    break;

            default:
                break;
        }
    }


    bool Logger::Debug(Level const& level, std::string_view message, std::function<void(void)> callback) {
        #if RPG_DEBUG
            Logger::Log(level, message);
            valid(callback)();

            return true;
        #endif

        return false;
    }
}