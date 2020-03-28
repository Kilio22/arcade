/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <filesystem>
#include <regex>
#include <list>
#include <dlfcn.h>

namespace Arcade
{
    /**
     * @brief Used for dynamically loading libraries.
     * @tparam T Library class type. Either IGameModule or IDisplayModule.
     */
    template <class T>
    class DLLoader
    {
        public:
            /**
             * @brief Gets the Instance object.
             * @return The current DLLoader instance.
             */
            static DLLoader const &getInstance(void);

            DLLoader(DLLoader const &) = delete;
            void operator=(DLLoader const &) = delete;

            ~DLLoader() = default;

            /**
             * @brief Gets the available libraries in a given folder.
             * @param dirPath Folder to lookup
             * @return std::vector<std::pair<std::string, std::string>> Vector containing [path, name] pairs.
             */
            std::vector<std::pair<std::string, std::string>> getLibraries(const std::string &dirPath) const;

            /**
             * @brief Loads the given library.
             * @param path File containing the library to extract.
             * @return std::unique_ptr<T> Unique pointer to the T instance.
             */
            std::unique_ptr<T> loadLibrary(const std::string &path) const;

        private:
            DLLoader() = default;

            using createLib_t = std::unique_ptr<T> (*)(void);

            static const std::regex libRegex;
            static DLLoader loaderInstance;
    };
}

#endif /* !DLLOADER_HPP_ */
