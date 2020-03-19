/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

const std::regex Arcade::DLLoader::libRegex("lib_arcade_.+\\.so");
Arcade::DLLoader Arcade::DLLoader::loaderInstance;

Arcade::DLLoader::DLLoader()
{
}

Arcade::DLLoader::~DLLoader()
{
}

Arcade::DLLoader &Arcade::DLLoader::getInstance(void)
{
    return Arcade::DLLoader::loaderInstance;
}

std::vector<std::string> Arcade::DLLoader::getLibraries(const std::string &dirPath)
{
    std::vector<std::string> libsPath;

    for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file() == false) {
            continue;
        }
        if (entry.path().string().find_last_of('/') == std::string::npos) {
            continue;
        }
        const std::string libName = entry.path().string().substr(entry.path().string().find_last_of('/') + 1);
        if (std::regex_match(libName, libRegex) == true && this->isValidLib(entry.path().string()) == true) {
            libsPath.push_back(entry.path().string());
        }
    }
    return libsPath;
}

bool Arcade::DLLoader::isValidLib(const std::string &path)
{
    void *handler = dlopen(path.c_str(), RTLD_NOW);
    void *createLib = nullptr;

    if (!handler) {
        std::cout << dlerror() << std::endl;
        return false;
    }
    createLib = dlsym(handler, "createLib");
    if (!createLib) {
        std::cout << dlerror() << std::endl;
        return false;
    }
    dlclose(handler);
    return true;
}