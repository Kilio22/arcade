/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGameModule
*/

#include "games/AGameModule.hpp"

const std::regex Arcade::Games::AGameModule::highscoreRegex("\\w*:\\d*$");

Arcade::Games::AGameModule::AGameModule(std::string const &libname)
    : _currentScore(0), _isDead(false), _playerName(""), _libName(libname)
{
}

Arcade::Games::AGameModule::~AGameModule()
{
    if (this->_highscores.empty() == false)
        this->saveToFile();
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
    this->sortHighscores();
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
    this->sortHighscores();
    return true;
}

bool Arcade::Games::AGameModule::saveToFile(const std::string &filepath) const
{
    std::ofstream ofs;

    ofs.open(filepath);
    for (auto tuple : this->_highscores) {
        ofs << tuple.first << ":" << tuple.second << std::endl;
    }
    ofs.close();
    return false;
}

bool Arcade::Games::AGameModule::saveToFile() const
{
    std::ofstream ofs;

    ofs.open(SAVE_PATH + this->_libName);
    for (auto tuple : this->_highscores) {
        ofs << tuple.first << ":" << tuple.second << std::endl;
    }
    ofs.close();
    return false;
}

void Arcade::Games::AGameModule::setPlayerName(const std::string &playerName)
{
    this->_playerName.assign(playerName);
}

std::vector<std::pair<std::string, int>> Arcade::Games::AGameModule::getBestScores(void) const
{
    if (this->_highscores.size() < 16)
        return this->_highscores;
    return {this->_highscores.begin(), this->_highscores.begin() + 16};
}

std::pair<std::string, int> Arcade::Games::AGameModule::getScore(void) const
{
    return {this->_playerName, this->_currentScore};
}

const std::string &Arcade::Games::AGameModule::getLibName() const
{
    return this->_libName;
}

/* Default game render if not overriden */
void Arcade::Games::AGameModule::render(Arcade::Display::IDisplayModule &lib) const
{
    lib.setColor(Display::IDisplayModule::Colors::WHITE);
    lib.putText("Sorry, game is out of order :(", 20, 10, 10);
}

void Arcade::Games::AGameModule::addToBestScores(int nb)
{
    if (nb == 0)
        return;
    this->_highscores.push_back({this->_playerName, nb});
    this->sortHighscores();
}

void Arcade::Games::AGameModule::sortHighscores(void)
{
    std::sort(this->_highscores.begin(), this->_highscores.end(), [](std::pair<std::string, int> const &first, std::pair<std::string, int> const &second) {
        if (first.second != second.second) {
            return first.second > second.second;
        } else {
            return first.first < second.first;
        }
    });
}

void Arcade::Games::AGameModule::drawGameOver(Arcade::Display::IDisplayModule &displayModule) const
{
    displayModule.setColor(Arcade::Display::IDisplayModule::Colors::WHITE);
    displayModule.putText("GAME OVER", 25, 230, 200);
    displayModule.putText("Press 'm' to go back to menu,", 20, 100, 300);
    displayModule.putText("or 'r' to reset the game.", 20, 130, 340);
}
