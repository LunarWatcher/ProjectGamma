#include "package/Package.hpp"
#include "stc/FS.hpp"

#include <stdexcept>

namespace upm {

inline void enable(const std::string& package) {
    auto split = StrUtil::splitString(package, "@", 1);
    auto name = split[0];
    auto version = split.size() == 1 ? throw std::runtime_error("Not implemented") : split[1];

    if (packages.find(name) == packages.end()) {
        std::cout << "Failed to find " << name << std::endl;
        return;
    }

    auto& packageInfo = packages.at(name);
    auto packagePath = fs::path("/opt/upm-bin") / (name + "-" + version);
    //fs::create_directory_symlink(std::path("/opt/upm-bin" / (name + "-" + version)));
    packageInfo.enable(packagePath);

}

}
