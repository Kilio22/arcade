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

Arcade::Display::Ncurses::Ncurses()
    : ADisplayModule("Ncurses")
{
}

Arcade::Display::Ncurses::~Ncurses()
{
}
