/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#include "lib/SDL.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SDL>();
}

Arcade::Display::SDL::SDL()
{
}

Arcade::Display::SDL::~SDL()
{
}
