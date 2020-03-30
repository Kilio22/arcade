/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <memory>
#include <ctime>
#include <iostream>
#include "arcade.h"
#include "Core.hpp"
#include "Logger.hpp"
#include "Exceptions/ArcadeException.hpp"

static int print_wrong_arg_number()
{
    std::cout << "The program only accepts one argument" << std::endl;
    return ARCADE_FAILURE;
}

int main(int ac, char *av[])
{
    if (ac != 2) {
        return print_wrong_arg_number();
    }
    std::srand(std::time(nullptr));
    try
    {
        Arcade::Logger::setLogLevel(Arcade::Logger::LogLevel::ERROR);
        Arcade::Core core(av[1]);

        core.play();
    }
    catch (const Arcade::Exceptions::ArcadeException &ex)
    {
        std::cerr << "An error occured while running the program : \"";
        std::cerr << ex.what();
        std::cerr << "\"";
        std::cerr << "at: " << ex.getComponent() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "An unexpeted error happened! " << ex.what() << std::endl;
    }
    return ARCADE_SUCCESS;
}
