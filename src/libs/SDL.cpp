/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#include "lib/SDL.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SDL>();
}

Arcade::Display::SDL::SDL()
{
}

Arcade::Display::SDL::~SDL()
{
}

// void Arcade::Display::SDL::reset()
// {

// }

// bool Arcade::Display::SDL::isOpen() const
// {

// }

// bool Arcade::Display::SDL::switchToNext_lib() const
// {

// }

// bool Arcade::Display::SDL::switchToPrevious_lib() const
// {

// }

// bool Arcade::Display::SDL::switchToNext_game() const
// {

// }

// bool Arcade::Display::SDL::switchToPrevious_game() const
// {

// }

// bool Arcade::Display::SDL::shouldBeRestarted() const
// {

// }

// bool Arcade::Display::SDL::shouldGoToMenu() const
// {

// }

// bool Arcade::Display::SDL::shouldExit() const
// {

// }

// bool Arcade::Display::SDL::isKeyPressed(IDisplayModule::Keys) const
// {

// }

// bool Arcade::Display::SDL::isKeyPressedOnce(IDisplayModule::Keys) const
// {

// }

// float Arcade::Display::SDL::getDelta() const
// {

// }

// void Arcade::Display::SDL::clear() const
// {

// }

// void Arcade::Display::SDL::update()
// {

// }

// void Arcade::Display::SDL::render() const
// {

// }

// char Arcade::Display::SDL::getKeyCode() const
// {

// }

// void Arcade::Display::SDL::setColor(IDisplayModule::Colors col)
// {

// }

// void Arcade::Display::SDL::putPixel(float x, float y) const
// {

// }

// void Arcade::Display::SDL::putLine(float x1, float y1, float x2, float y2) const
// {

// }

// void Arcade::Display::SDL::putRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::SDL::putFillRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::SDL::putCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::SDL::putFillCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::SDL::putText(const std::string &text, unsigned int size, float x, float y) const
// {

// }

// const std::string &Arcade::Display::SDL::getLibName() const
// {

// }
