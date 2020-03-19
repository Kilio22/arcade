/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <memory>
#include <iostream>
#include "arcade.h"
#include "DLLoader.hpp"
#include "lib/IDisplayModule.hpp"

static int print_wrong_arg_number()
{
    std::cout << "The program only accepts one argument" << std::endl;
    return ARCADE_FAILURE;
}

static int print_bad_arg()
{
    std::cout << "The given library file is not compatible with the program" << std::endl;
    return ARCADE_FAILURE;
}

int main(int ac, char *av[])
{
    if (ac != 2) {
        return print_wrong_arg_number();
    }
    std::vector<std::string> libs = Arcade::DLLoader::getInstance().getLibraries("./lib/");
    std::unique_ptr<Arcade::Display::IDisplayModule> currentLib = Arcade::DLLoader::getInstance().loadLibrary<Arcade::Display::IDisplayModule>(av[1]);
    if (currentLib == nullptr) {
        return print_bad_arg();
    }
    while (currentLib->isOpen() == true) {
        currentLib->clear();
        currentLib->update();
        if (currentLib->shouldExit())
            break;
        try {
            currentLib->putText("Hello, World!", 30, 100, 100);
        } catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return ARCADE_FAILURE;
        }
        currentLib->render();
    }
    return 0;
}
