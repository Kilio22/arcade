/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#include "lib/SFML.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SFML>();
}

Arcade::Display::SFML::SFML()
{
}

Arcade::Display::SFML::~SFML()
{
}
