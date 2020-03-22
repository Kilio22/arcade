/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include "lib/IDisplayModule.hpp"
#include "games/IGameModule.hpp"

const std::regex Arcade::DLLoader::libRegex("lib_arcade_.+\\.so");
Arcade::DLLoader Arcade::DLLoader::loaderInstance;

Arcade::DLLoader::DLLoader()
{
}

Arcade::DLLoader const &Arcade::DLLoader::getInstance(void)
{
    return Arcade::DLLoader::loaderInstance;
}

template <class T>
std::vector<std::pair<std::string, std::string>> Arcade::DLLoader::getLibraries(const std::string &dirPath) const
{
    std::vector<std::pair<std::string, std::string>> availableLibs;

    if (std::filesystem::is_directory(dirPath) == false) {
        return {};
    }
    for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file() == false) {
            continue;
        }
        if (entry.path().string().find_last_of('/') == std::string::npos) {
            continue;
        }
        const std::string libFileName = entry.path().string().substr(entry.path().string().find_last_of('/') + 1);
        const std::unique_ptr<T> lib = this->loadLibrary<T>(entry.path().string());
        if (std::regex_match(libFileName, libRegex) == true && lib != nullptr) {
            availableLibs.push_back(
                std::make_pair(
                    entry.path().string(),
                    lib->getLibName()
            ));
        }
    }
    return availableLibs;
}

template <class T>
std::unique_ptr<T> Arcade::DLLoader::loadLibrary(const std::string &path) const
{
    void *handler = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
    createLib_t<T> createLib = nullptr;
    std::unique_ptr<T> lib = nullptr;

    if (!handler) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }
    createLib = (createLib_t<T>)dlsym(handler, "createLib");
    if (!createLib) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }
    lib = createLib();
    dlclose(handler);
    return lib;
}

template std::vector<std::pair<std::string, std::string>> Arcade::DLLoader::getLibraries<Arcade::Display::IDisplayModule>(const std::string &dirPath) const;
template std::vector<std::pair<std::string, std::string>> Arcade::DLLoader::getLibraries<Arcade::Games::IGameModule>(const std::string &dirPath) const;

template std::unique_ptr<Arcade::Display::IDisplayModule> Arcade::DLLoader::loadLibrary(const std::string &path) const;
template std::unique_ptr<Arcade::Games::IGameModule> Arcade::DLLoader::loadLibrary(const std::string &path) const;
