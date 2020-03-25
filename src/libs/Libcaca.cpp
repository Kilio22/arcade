/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include "lib/Libcaca.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Libcaca>();
}

Arcade::Display::Libcaca::Libcaca()
{
}

Arcade::Display::Libcaca::~Libcaca()
{
}
