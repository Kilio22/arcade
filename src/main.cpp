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

static int print_wrong_arg_number()
{
    std::cout << "The program only accepts one argument" << std::endl;
    return ARCADE_FAILURE;
}

// static int print_bad_arg()
// {
//     std::cout << "The given library file is not compatible with the program" << std::endl;
//     return ARCADE_FAILURE;
// }

int main(int ac, char *av[])
{
    if (ac != 2) {
        return print_wrong_arg_number();
    }
    std::vector<std::string> oui = Arcade::DLLoader::getInstance().getLibraries("./lib/", av[1]);
    for (const std::string &value : oui) {
        std::cout << value << std::endl;
    }
    return 0;
}
