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
    float y = 7;
    int lineSize = 0;
    bool hasWall = false;

    if (ifs.is_open() == false)
        throw Arcade::Exceptions::BadFileException("Cannot load pacman map.", "Pacman::Pacman");
    std::getline(ifs, line);
    lineSize = line.size();
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    x = (WIDTH - lineSize * 15) / 2;
    while (std::getline(ifs, line)) {
        for (auto character = line.begin(); character < line.end(); character++) {
            if (*character == ' ' && hasWall == true) {
                this->_rects.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::BLACK});
                this->_cicles.push_back({x + 7, y + 7, 1, Arcade::Display::IDisplayModule::YELLOW});
            } else if (*character == '#') {
                hasWall = true;
                this->_rects.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::RED});
            }
            if (*character == 'O') {
                this->_rects.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::BLACK});
                this->_cicles.push_back({x + 2, y + 2, 5, Arcade::Display::IDisplayModule::LIGHT_BLUE});
            }
            x += 15;
        }
        hasWall = false;
        x = (WIDTH - lineSize * 15) / 2;
        y += 15;
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
    for (auto oui = this->_cicles.begin(); oui < this->_cicles.end(); oui++) {
        displayModule.setColor(oui->color);
        displayModule.putFillCircle(oui->x, oui->y, oui->radius);
    }
    for (auto oui = this->_pixels.begin(); oui < this->_pixels.end(); oui++) {
        displayModule.setColor(oui->color);
        displayModule.putPixel(oui->x, oui->y);
    }
}
