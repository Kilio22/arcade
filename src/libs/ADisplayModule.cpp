/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ADisplayModule
*/

#include "lib/ADisplayModule.hpp"

Arcade::Display::ADisplayModule::ADisplayModule(const std::string &libName)
    : libName(libName)
{
}

const std::string &Arcade::Display::ADisplayModule::getLibName() const
{
    return this->libName;
}
