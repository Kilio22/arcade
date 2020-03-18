/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#include "lib/NCurses.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::NCurses>();
}

Arcade::Display::NCurses::NCurses()
{
}

Arcade::Display::NCurses::~NCurses()
{
}

// void Arcade::Display::NCurses::reset()
// {

// }

// bool Arcade::Display::NCurses::isOpen() const
// {

// }

// bool Arcade::Display::NCurses::switchToNext_lib() const
// {

// }

// bool Arcade::Display::NCurses::switchToPrevious_lib() const
// {

// }

// bool Arcade::Display::NCurses::switchToNext_game() const
// {

// }

// bool Arcade::Display::NCurses::switchToPrevious_game() const
// {

// }

// bool Arcade::Display::NCurses::shouldBeRestarted() const
// {

// }

// bool Arcade::Display::NCurses::shouldGoToMenu() const
// {

// }

// bool Arcade::Display::NCurses::shouldExit() const
// {

// }

// bool Arcade::Display::NCurses::isKeyPressed(IDisplayModule::Keys) const
// {

// }

// bool Arcade::Display::NCurses::isKeyPressedOnce(IDisplayModule::Keys) const
// {

// }

// float Arcade::Display::NCurses::getDelta() const
// {

// }

// void Arcade::Display::NCurses::clear() const
// {

// }

// void Arcade::Display::NCurses::update()
// {

// }

// void Arcade::Display::NCurses::render() const
// {

// }

// char Arcade::Display::NCurses::getKeyCode() const
// {

// }

// void Arcade::Display::NCurses::setColor(IDisplayModule::Colors col)
// {

// }

// void Arcade::Display::NCurses::putPixel(float x, float y) const
// {

// }

// void Arcade::Display::NCurses::putLine(float x1, float y1, float x2, float y2) const
// {

// }

// void Arcade::Display::NCurses::putRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::NCurses::putFillRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::NCurses::putCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::NCurses::putFillCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::NCurses::putText(const std::string &text, unsigned int size, float x, float y) const
// {

// }

// const std::string &Arcade::Display::NCurses::getLibName() const
// {

// }
