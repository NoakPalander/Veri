#pragma once

// Checks the compiler version
#if __GNUC__ < 8 || __clang__ == 1 && __clang_major__ < 6
    // Includes filesystem from experimental
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    // Includes filesystem from stable
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

#include <string>

inline std::string FindFile(std::string name) {
    if (!fs::exists(name)) {
        name.erase(std::begin(name), std::begin(name) + 3);
        return fs::absolute(name).string();
    }

    return fs::absolute(name).string();
}