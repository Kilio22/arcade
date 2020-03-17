/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <memory>
#include "DLLoader.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    std::vector<std::string> oui = Arcade::DLLoader::getInstance().getLibraries("./lib/", av[1]);
    for (const std::string &value : oui) {
        std::cout << value << std::endl;
    }
    return 0;
}
