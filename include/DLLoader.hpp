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
#include <dlfcn.h>

namespace Arcade
{
    class DLLoader
    {
        public:
            static DLLoader &getInstance(void);
            DLLoader(DLLoader const &) = delete;
            void operator=(DLLoader const &) = delete;

            ~DLLoader();

            bool isValidLib(const std::string &path);
            std::vector<std::string> getLibraries(const std::string &dirPath, std::string fst);
            template <class T>
            std::unique_ptr<T> loadLibrary(const std::string &path);

            template <class T>
            using createLib_t = std::unique_ptr<T> (*)(void);

        protected:
        private:
            DLLoader();
            static const std::regex libRegex;
            static DLLoader loaderInstance;
    };
}

#endif /* !DLLOADER_HPP_ */
