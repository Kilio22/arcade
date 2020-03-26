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

Arcade::Display::Libcaca::Libcaca()
    : _canvas(nullptr), _display(nullptr)
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

const std::string &Arcade::Display::Libcaca::getLibName() const
{
    return this->_libName;
}