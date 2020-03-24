/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "games/Pacman.hpp"
#include "Exceptions/BadFileException.hpp"

const std::string Arcade::Games::Pacman::_mapPath = "./src/games/Pacman/maze.txt";

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Pacman>();
}

Arcade::Games::Pacman::Pacman()
    : AGameModule("Pacman")
{
    std::ifstream ifs(this->_mapPath);
    std::string line;
    float x = 0;
    float y = 0;
    int lineSize = 0;

    if (ifs.is_open() == false)
        throw Arcade::Exceptions::BadFileException("Cannot load pacman map.", "Pacman::Pacman");
    std::getline(ifs, line);
    lineSize = line.size();
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    x = lineSize;
    while (std::getline(ifs, line)) {
        for (auto character = line.begin(); character < line.end(); character++) {
            if (*character == ' ') {
                this->_rects.push_back({x, y, 15, 20, Arcade::Display::IDisplayModule::BLACK});
            } else {
                this->_rects.push_back({x, y, 15, 20, Arcade::Display::IDisplayModule::RED});
            }
            x += 15;
        }
        x = lineSize;
        y += 20;
    }
    ifs.close();
}

Arcade::Games::Pacman::Pacman::~Pacman()
{
}

void Arcade::Games::Pacman::reset()
{

}

void Arcade::Games::Pacman::update(const Arcade::Display::IDisplayModule &)
{

}

void Arcade::Games::Pacman::render(Arcade::Display::IDisplayModule &displayModule) const
{
    for (auto oui = this->_rects.begin(); oui < this->_rects.end(); oui++) {
        displayModule.setColor(oui->color);
        displayModule.putFillRect(oui->x, oui->y, oui->w, oui->h);
    }
}
