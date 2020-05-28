#pragma once

#include "spdlog/spdlog.h"
#include <string>
#include <string_view>
#include <functional>
#include <vector>

namespace Veri { namespace Logger {
    enum class Level {
        Trace       = spdlog::level::trace, 
        Info        = spdlog::level::info,
        Warn        = spdlog::level::warn,
        Critical    = spdlog::level::critical,
    };

    void Init(std::string const& branch, std::string_view mode, std::string const& title = "RPG");
    void Log(Level const& level, std::string_view message);
    bool Debug(Level const& level, std::string_view message, std::function<void(void)> callback = nullptr);
}}