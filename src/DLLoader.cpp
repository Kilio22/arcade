/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include "Logger.hpp"
#include "games/IGameModule.hpp"
#include "lib/IDisplayModule.hpp"

template <class T>
const std::regex Arcade::DLLoader<T>::libRegex("lib_arcade_.+\\.so");
template <class T>
Arcade::DLLoader<T> Arcade::DLLoader<T>::loaderInstance;

template <class T>
const Arcade::DLLoader<T> &Arcade::DLLoader<T>::getInstance(void)
{
    return Arcade::DLLoader<T>::loaderInstance;
}

template <class T>
std::vector<Arcade::DLInfos> Arcade::DLLoader<T>::getLibraries(const std::string &dirPath) const
{
    std::vector<DLInfos> availableLibs;

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
        const std::unique_ptr<T> lib = this->loadLibrary(entry.path().string());
        if (std::regex_match(libFileName, libRegex) == true && lib != nullptr) {
            availableLibs.push_back({ entry.path().string(), lib->getLibName(), this->getBestScores(lib) });
        }
    }
    return availableLibs;
}

template <class T>
std::unique_ptr<T> Arcade::DLLoader<T>::loadLibrary(const std::string &path) const
{
    void *handler = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
    createLib_t createLib = nullptr;
    std::unique_ptr<T> lib = nullptr;

    if (!handler) {
        Logger::log(Logger::ERROR, dlerror());
        return nullptr;
    }
    createLib = (createLib_t)dlsym(handler, "createLib");
    if (!createLib) {
        Logger::log(Logger::ERROR, dlerror());
        return nullptr;
    }
    lib = createLib();
    dlclose(handler);
    return lib;
}

template <>
std::vector<std::pair<std::string, int>> Arcade::DLLoader<Arcade::Display::IDisplayModule>::getBestScores(const std::unique_ptr<Arcade::Display::IDisplayModule> &) const
{
    return {};
}

template <>
std::vector<std::pair<std::string, int>> Arcade::DLLoader<Arcade::Games::IGameModule>::getBestScores(const std::unique_ptr<Arcade::Games::IGameModule> &lib) const
{
    lib->loadFromFile();
    return lib->getBestScores();
}

template class Arcade::DLLoader<Arcade::Display::IDisplayModule>;
template class Arcade::DLLoader<Arcade::Games::IGameModule>;
