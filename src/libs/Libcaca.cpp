/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include "lib/Libcaca.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Licaca>();
}

Arcade::Display::Licaca::Licaca()
{
}

Arcade::Display::Licaca::~Licaca()
{
}

// void Arcade::Display::Licaca::reset()
// {

// }

// bool Arcade::Display::Licaca::isOpen() const
// {

// }

// bool Arcade::Display::Licaca::switchToNext_lib() const
// {

// }

// bool Arcade::Display::Licaca::switchToPrevious_lib() const
// {

// }

// bool Arcade::Display::Licaca::switchToNext_game() const
// {

// }

// bool Arcade::Display::Licaca::switchToPrevious_game() const
// {

// }

// bool Arcade::Display::Licaca::shouldBeRestarted() const
// {

// }

// bool Arcade::Display::Licaca::shouldGoToMenu() const
// {

// }

// bool Arcade::Display::Licaca::shouldExit() const
// {

// }

// bool Arcade::Display::Licaca::isKeyPressed(IDisplayModule::Keys) const
// {

// }

// bool Arcade::Display::Licaca::isKeyPressedOnce(IDisplayModule::Keys) const
// {

// }

// float Arcade::Display::Licaca::getDelta() const
// {

// }

// void Arcade::Display::Licaca::clear() const
// {

// }

// void Arcade::Display::Licaca::update()
// {

// }

// void Arcade::Display::Licaca::render() const
// {

// }

// char Arcade::Display::Licaca::getKeyCode() const
// {

// }

// void Arcade::Display::Licaca::setColor(IDisplayModule::Colors col)
// {

// }

// void Arcade::Display::Licaca::putPixel(float x, float y) const
// {

// }

// void Arcade::Display::Licaca::putLine(float x1, float y1, float x2, float y2) const
// {

// }

// void Arcade::Display::Licaca::putRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::Licaca::putFillRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::Licaca::putCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::Licaca::putFillCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::Licaca::putText(const std::string &text, unsigned int size, float x, float y) const
// {

// }

// const std::string &Arcade::Display::Licaca::getLibName() const
// {

// }
