/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Qix
*/

#include "games/Qix.hpp"

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Qix>();
}

Arcade::Games::Qix::Qix()
    : AGameModule("Qix")
{
}

void Arcade::Games::Qix::reset()
{
}

void Arcade::Games::Qix::update(const Arcade::Display::IDisplayModule &)
{
}
