/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#include "NCurses.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::NCurses>();
}

Arcade::Display::NCurses::NCurses()
{
}

Arcade::Display::NCurses::~NCurses()
{
}
