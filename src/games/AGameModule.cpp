/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGameModule
*/

#include "games/AGameModule.hpp"

const std::regex Arcade::Games::AGameModule::highscoreRegex("\\w*:\\d*$");

Arcade::Games::AGameModule::AGameModule(std::string const &libname)
    : _playerName(""), _libName(libname)
{
}

bool Arcade::Games::AGameModule::loadFromFile(const std::string &filepath)
{
    std::ifstream ifs;
    std::string line;

    ifs.open(filepath);
    if (ifs.is_open() == false)
        return false;
    while (std::getline(ifs, line)) {
        if (std::regex_match(line, this->highscoreRegex) == false)
            return false;
        this->_highscores.push_back({line.substr(0, line.find(':')), std::stoi(line.substr(line.find(':') + 1))});
    }
    ifs.close();
    return true;
}

bool Arcade::Games::AGameModule::loadFromFile()
{
    std::ifstream ifs;
    std::string line;

    ifs.open(SAVE_PATH + this->_libName);
    if (ifs.is_open() == false)
        return false;
    while (std::getline(ifs, line)) {
        if (std::regex_match(line, this->highscoreRegex) == false)
            return false;
        this->_highscores.push_back({line.substr(0, line.find(':')), std::stoi(line.substr(line.find(':') + 1))});
    }
    ifs.close();
    return true;
}

bool Arcade::Games::AGameModule::saveToFile(const std::string &filepath) const
{
    std::ofstream ofs;

    ofs.open(filepath);
    for (auto tuple : this->_highscores) {
        ofs << std::get<0>(tuple) << ":" << std::get<1>(tuple) << std::endl;
    }
    ofs.close();
    return false;
}

bool Arcade::Games::AGameModule::saveToFile() const
{
    std::ofstream ofs;

    ofs.open(SAVE_PATH + this->_libName);
    for (auto tuple : this->_highscores) {
        ofs << std::get<0>(tuple) << ":" << std::get<1>(tuple) << std::endl;
    }
    ofs.close();
    return false;
}

void Arcade::Games::AGameModule::setPlayerName(const std::string &playerName)
{
    this->_playerName.assign(playerName);
}

std::tuple<std::string, int> Arcade::Games::AGameModule::getHighscore() const
{
    if (this->_highscores.size() == 0)
        return {};
    return this->_highscores.at(0);
}

std::vector<std::tuple<std::string, int>> Arcade::Games::AGameModule::getLatestScores() const
{
    if (this->_highscores.size() < 16)
        return this->_highscores;
    return {this->_highscores.begin(), this->_highscores.begin() + 16};
}

const std::string &Arcade::Games::AGameModule::getLibName() const
{
    return this->_libName;
}