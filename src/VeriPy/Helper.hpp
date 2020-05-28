#pragma once

#include "../Logic/Timer.hpp"
#include "../Logic/Filesystem.hpp"
#include <string>
#include <tuple>

namespace VeriPy {
    inline std::string FindFile(std::string name) {
        if (!fs::exists(name)) {
            name.erase(std::begin(name), std::begin(name) + 3);
            return fs::absolute(name).string();
        }

        return fs::absolute(name).string();
    }

    inline std::pair<float, float> ToGlobalCoord(uint sceneWidth) {
        // implement a convertion that returns a global position..
        return std::make_pair(0.f, 0.f);
    }

    inline void Sleep(uint milliseconds) {
        Veri::Timer::Sleep(Veri::Timer::MilliSeconds(milliseconds));
    }

    inline void SleepOnce(uint milliseconds) {
        static bool hasSlept = false;
        if (!hasSlept)
            Sleep(milliseconds);
    }
}