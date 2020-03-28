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
#include "DLInfos.h"

namespace Arcade
{
    /**
     * @brief Used for dynamically loading libraries.
     * @tparam T Library class type. <b>Either Arcade::Games::IGameModule or Arcade::Display::IDisplayModule</b>.
     */
    template <class T>
    class DLLoader
    {
        public:
            /**
             * @brief Gets an instance of this object.
             * @return The current DLLoader instance.
             */
            static DLLoader const &getInstance(void);

            DLLoader(DLLoader const &) = delete;
            void operator=(DLLoader const &) = delete;

            ~DLLoader() = default;

            /**
             * @brief Gets the available libraries in a given folder.
             * @param dirPath Folder to lookup
             * @return std::vector<DLInfos> Vector containing informations about the library.
             */
            std::vector<DLInfos> getLibraries(const std::string &dirPath) const;

            /**
             * @brief Loads the given library.
             * @param path File containing the library to extract.
             * @return std::unique_ptr<T> Unique pointer to the T instance.
             */
            std::unique_ptr<T> loadLibrary(const std::string &path) const;

        private:
            DLLoader() = default;

            std::vector<std::pair<std::string, int>> getBestScores(const std::unique_ptr<T> &lib) const;

            using createLib_t = std::unique_ptr<T> (*)(void);

            static const std::regex libRegex;
            static DLLoader loaderInstance;
    };
}

#endif /* !DLLOADER_HPP_ */
