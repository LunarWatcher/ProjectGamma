#include <algorithm>
#include <iostream>

#include "platform/Platform.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include "Context.hpp"

// TODO: merge into stc (haven't I already?)
std::string toLower(std::string in) {
    std::transform(in.begin(), in.end(), in.begin(),
        [](const char& c) {
            return std::tolower(c);
        });
    return in;
}

int main(int argc, const char* argv[]) {
    spdlog::set_pattern("[%^%l%$] %v");
    spdlog::cfg::load_env_levels();

    std::vector<std::string> arguments;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("--debug")) {
            spdlog::set_level(spdlog::level::debug);
        } else {
            arguments.push_back(argv[i]);
        }
    }
    if (arguments.size() == 0) {
        arguments.push_back("help");
    }

    upm::Context ctx(arguments);
    try {
        return ctx.run();
    } catch (const std::exception& e) {
        spdlog::error("Aborting with message: {}", e.what());
    } catch(const std::string& e) {
        spdlog::error("Aborting with message: {}", e);
    } catch(const char* e) {
        spdlog::error("Aborting with message: {}", e);
    }
}
