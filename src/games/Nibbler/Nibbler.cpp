/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include "games/Nibbler.hpp"

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Nibbler>();
}

Arcade::Games::Nibbler::Nibbler()
    : AGameModule("Nibbler")
{
}

void Arcade::Games::Nibbler::reset()
{
}

void Arcade::Games::Nibbler::update(const Arcade::Display::IDisplayModule &)
{
}
