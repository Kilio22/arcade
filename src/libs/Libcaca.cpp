/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include <algorithm>
#include "lib/Libcaca.hpp"
#include "Exceptions/BadInstanciationException.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Libcaca>();
}

const std::vector<caca_color> Arcade::Display::Libcaca::_libColors = {
    caca_color::CACA_BLACK,
    caca_color::CACA_BLACK,
    caca_color::CACA_RED,
    caca_color::CACA_GREEN,
    caca_color::CACA_YELLOW,
    caca_color::CACA_BLUE,
    caca_color::CACA_MAGENTA,
    caca_color::CACA_CYAN,
    caca_color::CACA_LIGHTGRAY,
    caca_color::CACA_DARKGRAY,
    caca_color::CACA_LIGHTRED,
    caca_color::CACA_LIGHTGREEN,
    caca_color::CACA_YELLOW,
    caca_color::CACA_LIGHTBLUE,
    caca_color::CACA_LIGHTMAGENTA,
    caca_color::CACA_LIGHTCYAN,
    caca_color::CACA_WHITE
};

const std::vector<int> Arcade::Display::Libcaca::_libKeys = {
    CACA_KEY_LEFT,
    CACA_KEY_RIGHT,
    CACA_KEY_UP,
    CACA_KEY_DOWN,
    'z',
    'q',
    's',
    'd',
    'a',
    'e',
    'w',
    'x',
    ' ',
    'j',
    'k',
    'u',
    'i',
    CACA_KEY_RETURN,
    CACA_KEY_ESCAPE,
    'm',
    'r',
    CACA_KEY_F1,
    CACA_KEY_F2,
    CACA_KEY_F3,
    CACA_KEY_F4,
};

Arcade::Display::Libcaca::Libcaca() : ADisplayModule("Libcaca"),
    _canvas(nullptr), _display(nullptr), _events(SystemKeys::SYSKEYS_END, false),
    _currentColor(Colors::DEFAULT), _isOpen(false), _keyCode('\0'),
    _shouldClose(false)
{
}

Arcade::Display::Libcaca::~Libcaca()
{
    this->close();
}

void Arcade::Display::Libcaca::reset()
{
    this->clear();
}

void Arcade::Display::Libcaca::open()
{
    _canvas = caca_create_canvas(FULL_WIDTH / 8, FULL_HEIGHT / 16);
    _display = caca_create_display(_canvas);
    if (!_display)
        throw Arcade::Exceptions::BadInstanciationException("display creation failed.", "Libcaca::open");
    caca_set_display_title(_display, "Libcaca");
    _isOpen = true;
}

void Arcade::Display::Libcaca::close()
{
    if (this->_display != nullptr)
        caca_free_display(_display);
    if (this->_canvas != nullptr)
        caca_free_canvas(_canvas);
    _display = nullptr;
    _canvas = nullptr;
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
    return this->_events.at(SystemKeys::ESCAPE) || this->_shouldClose;
}

bool Arcade::Display::Libcaca::isKeyPressed(Keys key) const
{
    return this->_events.at(key);
}

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
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
	caca_clear_canvas(_canvas);
}

void Arcade::Display::Libcaca::update()
{
    caca_event_t event;
    caca_event_type type;

    this->_events.assign(SystemKeys::SYSKEYS_END, false);
    this->_keyCode = '\0';
    if (caca_get_event(_display, CACA_EVENT_ANY, &event, 0) == 1) {
        type = caca_get_event_type(&event);
        if (type == CACA_EVENT_KEY_PRESS) {
            int key = caca_get_event_key_ch(&event);
            this->_keyCode = key;
            auto found = std::find(this->_libKeys.begin(), this->_libKeys.end(), key);
            if (found != this->_libKeys.end())
                this->_events[std::distance(this->_libKeys.begin(), found)] = true;
        }
        else if (type == CACA_EVENT_QUIT)
            this->_shouldClose = true;
    }
}

void Arcade::Display::Libcaca::render() const
{
	caca_refresh_display(_display);
    usleep(16666);
}

char Arcade::Display::Libcaca::getKeyCode() const
{
    if (this->_keyCode == '\b')
        return this->_keyCode;
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

void Arcade::Display::Libcaca::setColor(IDisplayModule::Colors color)
{
    this->_currentColor = color;
}

void Arcade::Display::Libcaca::putPixel(float x, float y) const
{
    this->putRect(x, y, 1, 1);
}

void Arcade::Display::Libcaca::putLine(float x1, float y1, float x2, float y2) const
{
    caca_set_color_ansi(_canvas, this->_libColors.at(this->_currentColor), CACA_BLACK);
    caca_draw_line(_canvas, x1, y1, x2, y2, 9642);
}

void Arcade::Display::Libcaca::putRect(float x, float y, float w, float h) const
{
    caca_set_color_ansi(_canvas, CACA_BLACK, this->_libColors.at(this->_currentColor));
    if (w < 32 || h < 32)
        return this->putFillRect(x, y, w, h);
    caca_draw_box(this->_canvas, x / 8 + caca_get_canvas_width(_canvas) / 2 - 40, y / 16 + caca_get_canvas_height(_canvas) / 2 - 10, w / 8, h / 16, ' ');
}

void Arcade::Display::Libcaca::putFillRect(float x, float y, float w, float h) const
{
    caca_set_color_ansi(_canvas, CACA_BLACK, this->_libColors.at(this->_currentColor));
    caca_fill_box(_canvas, x / 8 + caca_get_canvas_width(_canvas) / 2 - 40, y / 16 + caca_get_canvas_height(_canvas) / 2 - 10, w / 8, h / 16, ' ');
}

void Arcade::Display::Libcaca::putCircle(float x, float y, float) const
{
    caca_set_color_ansi(_canvas, this->_libColors.at(this->_currentColor), CACA_BLACK);
    caca_draw_circle(_canvas, x / 8 + caca_get_canvas_width(_canvas) / 2 - 40, y / 16 + caca_get_canvas_height(_canvas) / 2 - 10, 0, 'o');
}

void Arcade::Display::Libcaca::putFillCircle(float x, float y, float) const
{
    caca_set_color_ansi(_canvas, this->_libColors.at(this->_currentColor), CACA_BLACK);
    caca_draw_circle(_canvas, x / 8 + caca_get_canvas_width(_canvas) / 2 - 40, y / 16 + caca_get_canvas_height(_canvas) / 2 - 10, 0, 9675);
}

void Arcade::Display::Libcaca::putText(const std::string &text, unsigned int, float x, float y) const
{
    caca_set_color_ansi(_canvas, this->_libColors.at(this->_currentColor), CACA_BLACK);
    if (x < 0) {
        x *= -1;
        y *= -1;
        caca_put_str(_canvas, x / 8, y / 16, text.c_str());
    } else if (x >= 0) {
        caca_put_str(_canvas, x / 8 + caca_get_canvas_width(_canvas) / 2 - 40, y / 16 + caca_get_canvas_height(_canvas) / 2 - 10, text.c_str());
    }
}