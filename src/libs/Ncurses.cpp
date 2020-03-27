/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include "lib/Ncurses.hpp"
#include "Exceptions/BadInstanciationException.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Ncurses>();
}

const std::string Arcade::Display::Ncurses::_libName = "Libcaca";

Arcade::Display::Ncurses::Ncurses()
{
}

Arcade::Display::Ncurses::~Ncurses()
{
}
