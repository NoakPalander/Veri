#pragma once        // Include-guard

#include <chrono>   // std::chrono
#include <variant>  // std::variant
#include <thread>   // std::this_thread


namespace Veri { namespace Timer {
    // Holds 1 of the listed types
    using Duration = std::variant<
        std::chrono::nanoseconds, 
        std::chrono::microseconds, 
        std::chrono::milliseconds, 
        std::chrono::seconds, 
        std::chrono::minutes, 
        std::chrono::hours
    >;  
    
    constexpr inline auto NanoSeconds(ulong time)  { return std::chrono::nanoseconds(time);  } // ns
    constexpr inline auto MicroSeconds(ulong time) { return std::chrono::microseconds(time); } // us
    constexpr inline auto MilliSeconds(ulong time) { return std::chrono::milliseconds(time); } // ms
    constexpr inline auto Seconds(ulong time)      { return std::chrono::seconds(time);      } // s
    constexpr inline auto Minutes(ulong time)      { return std::chrono::minutes(time);      } // m
    constexpr inline auto Hours(ulong time)        { return std::chrono::hours(time);        } // h

    // Sleeps with a generic duration
    inline void Sleep(Duration const& duration) {
       // Calls sleep with the avalible option in variant
       std::visit([](auto&& time) { std::this_thread::sleep_for(time); }, duration);
    }
}}