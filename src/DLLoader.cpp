/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

const std::regex Arcade::DLLoader::libRegex("lib_arcade_.+\\.so");

Arcade::DLLoader::DLLoader()
{
}

Arcade::DLLoader::~DLLoader()
{
}

std::vector<std::string> Arcade::DLLoader::getLibraries(const std::string &dirPath, std::string fst)
{
    std::vector<std::string> libsPath;

    if (fst.compare(0, 2, "./") != 0) {
        fst = "./" + fst;
    }
    std::string firstLibName = fst.substr(fst.find_last_of('/') + 1);
    if (std::filesystem::is_directory(dirPath) == false || std::regex_match(firstLibName, libRegex) == false || this->isValidLib(fst) == false) {
        return libsPath;
    }
    libsPath.push_back(fst);
    for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file() == false) {
            continue;
        }
        if (entry.path().string().find_last_of('/') == std::string::npos) {
            continue;
        }
        const std::string libName = entry.path().string().substr(entry.path().string().find_last_of('/') + 1);
        if (std::regex_match(libName, libRegex) == true && libName.compare(firstLibName) != 0 && this->isValidLib(entry.path().string()) == true) {
            libsPath.push_back(entry.path().string());
        }
    }
    return libsPath;
}

template <class T>
std::unique_ptr<T> Arcade::DLLoader::loadLibrary(const std::string &path)
{
    void *handler = dlopen(path.c_str(), RTLD_LAZY);
    createLib_t <T>createLib = nullptr;
    std::unique_ptr<T> lib = nullptr;

    if (!handler) {
        std::cout << dlerror() << std::endl;
        return nullptr;
    }
    createLib = dlsym(handler, "createLib");
    if (!createLib) {
        std::cout << dlerror() << std::endl;
        return nullptr;
    }
    lib = createLib();
    dlclose(handler);
    return lib;
}

bool Arcade::DLLoader::isValidLib(const std::string &path)
{
    void *handler = dlopen(path.c_str(), RTLD_LAZY);
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