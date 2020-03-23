/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGameModule
*/

#include "games/AGameModule.hpp"

Arcade::Games::AGameModule::AGameModule(std::string const &libname)
    : _playerName(""), _libName(libname)
{
}

Arcade::Games::AGameModule::~AGameModule()
{
}

bool Arcade::Games::AGameModule::loadFromFile(const std::string &)
{
    return false;
}

bool Arcade::Games::AGameModule::loadFromFile()
{
    return false;
}

bool Arcade::Games::AGameModule::saveToFile(const std::string &) const
{
    return false;
}

bool Arcade::Games::AGameModule::saveToFile() const
{
    return false;
}

void Arcade::Games::AGameModule::setPlayerName(const std::string &)
{

}

std::tuple<std::string, int> Arcade::Games::AGameModule::getHighscore() const
{
    return {};
}

std::vector<std::tuple<std::string, int>> Arcade::Games::AGameModule::getLatestScores() const
{
    return {};
}

const std::string &Arcade::Games::AGameModule::getLibName() const
{
    return this->_libName;
}