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
#include <dlfcn.h>
#include <iostream>
#include <filesystem>
#include <regex>

class DLLoader
{
    public:
        DLLoader();
        ~DLLoader();

        std::vector<std::string> getLibraries(const std::string &dirPath, std::string fst);
        template <class T>
        std::unique_ptr<T> loadLibrary(const std::string &path);

        template <class T>
        using createLib_t = std::unique_ptr<T> (*)(void);

    protected:
    private:
        static const std::regex libRegex;
};

#endif /* !DLLOADER_HPP_ */
