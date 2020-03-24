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

void Arcade::Games::Nibbler::update(const Arcade::Display::IDisplayModule &lib)
{
    (void)lib;
}

void Arcade::Games::Nibbler::render(Arcade::Display::IDisplayModule &lib) const
{
    lib.setColor(Display::IDisplayModule::Colors::WHITE);
    lib.putText("Sorry, game is out of order :(", 20, 10, 10);
}
