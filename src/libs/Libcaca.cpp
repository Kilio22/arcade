/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include "lib/Libcaca.hpp"
#include "Exceptions/BadInstanciationException.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Libcaca>();
}

const std::string Arcade::Display::Libcaca::_libName = "Libcaca";

Arcade::Display::Libcaca::Libcaca() : ADisplayModule("Libcaca"),
    _canvas(nullptr), _display(nullptr), _events(Keys::KEYS_END, false), _isOpen(false), _keyCode('\0')
{
}

Arcade::Display::Libcaca::~Libcaca()
{
    caca_free_display(_display);
}

void Arcade::Display::Libcaca::reset()
{
    this->clear();
}

void Arcade::Display::Libcaca::open()
{
    _canvas = caca_create_canvas(WIDTH, HEIGHT);
    _display = caca_create_display(_canvas);
    if (!_display)
        throw Arcade::Exceptions::BadInstanciationException("display creation failed.", "Libcaca::open");
    _isOpen = true;
}

bool Arcade::Display::Libcaca::isOpen() const
{
    return this->_isOpen;
}

bool Arcade::Display::Libcaca::switchToNextLib() const
{
    return this->_events.at(SystemKeys::F2);
}

bool Arcade::Display::Libcaca::switchToPreviousLib() const
{
    return this->_events.at(SystemKeys::F1);
}

bool Arcade::Display::Libcaca::switchToNextGame() const
{
    return this->_events.at(SystemKeys::F4);
}

bool Arcade::Display::Libcaca::switchToPreviousGame() const
{
    return this->_events.at(SystemKeys::F3);
}

bool Arcade::Display::Libcaca::shouldBeRestarted() const
{
    return this->_events.at(SystemKeys::R);
}

bool Arcade::Display::Libcaca::shouldGoToMenu() const
{
    return this->_events.at(SystemKeys::M);
}

bool Arcade::Display::Libcaca::shouldExit() const
{
    return this->_events.at(SystemKeys::ESCAPE);
}

// bool Arcade::Display::Libcaca::isKeyPressed(Keys key) const
// {

// }

bool Arcade::Display::Libcaca::isKeyPressedOnce(Keys key) const
{
    return this->_events.at(key);
}

float Arcade::Display::Libcaca::getDelta() const
{
    return 1;
}

void Arcade::Display::Libcaca::clear() const
{
	caca_set_color_argb(_canvas, 0, 0);
	caca_clear_canvas(_canvas);
}

void Arcade::Display::Libcaca::update()
{
	caca_refresh_display(_display);
}

void Arcade::Display::Libcaca::render() const
{
    //caca_render_canvas(_canvas,)
}

char Arcade::Display::Libcaca::getKeyCode() const
{
    if (this->_keyCode == '\b')
        return this->_keyCode;
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

// void Arcade::Display::Libcaca::setColor(IDisplayModule::Colors col)
// {

// }

// void Arcade::Display::Libcaca::putPixel(float x, float y) const
// {

// }

// void Arcade::Display::Libcaca::putLine(float x1, float y1, float x2, float y2) const
// {

// }

// void Arcade::Display::Libcaca::putRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::Libcaca::putFillRect(float x, float y, float w, float h) const
// {

// }

// void Arcade::Display::Libcaca::putCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::Libcaca::putFillCircle(float x, float y, float rad) const
// {

// }

// void Arcade::Display::Libcaca::putText(const std::string &text, unsigned int size, float x, float y) const
// {

// }