/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Solarfox
*/

#include "games/Solarfox.hpp"

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Solarfox>();
}

Arcade::Games::Solarfox::Solarfox()
    : AGameModule("Solarfox")
{
}

void Arcade::Games::Solarfox::reset()
{
}

void Arcade::Games::Solarfox::update(const Arcade::Display::IDisplayModule &)
{
}
