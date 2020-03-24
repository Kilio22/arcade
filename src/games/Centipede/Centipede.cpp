/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Centipede
*/

#include "games/Centipede.hpp"

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Centipede>();
}

Arcade::Games::Centipede::Centipede()
    : AGameModule("Centipede")
{
}

void Arcade::Games::Centipede::reset()
{
}

void Arcade::Games::Centipede::update(const Arcade::Display::IDisplayModule &)
{
}
