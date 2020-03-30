/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include <algorithm>
#include <unistd.h>
#include <math.h>
#include "lib/Ncurses.hpp"
#include "Exceptions/BadInstanciationException.hpp"

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::Ncurses>();
}

const std::vector<int> Arcade::Display::Ncurses::_libKeys = {
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
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
    '\n',
    27, // ESCAPE
    'm',
    'r',
    265, // F1
    266, // F2
    267, // F3
    268, // F4
};

const std::vector<std::pair<int, int>> Arcade::Display::Ncurses::_colorsToInit = {
    {COLOR_BLACK, COLOR_BLACK}, // DEFAULT
    {COLOR_BLACK, COLOR_BLACK}, // BLACK
    {COLOR_RED, COLOR_RED}, // RED
    {COLOR_GREEN, COLOR_GREEN}, // GREEN
    {COLOR_YELLOW, COLOR_YELLOW}, // YELLOW
    {COLOR_BLUE, COLOR_BLUE}, // BLUE
    {COLOR_MAGENTA, COLOR_MAGENTA}, // MAGENTA
    {COLOR_CYAN, COLOR_CYAN}, // CYAN
    {COLOR_WHITE, COLOR_WHITE}, // LIGHT GRAY
    {COLOR_BLACK, COLOR_BLACK}, // DARK GRAY
    {COLOR_RED, COLOR_RED}, // LIGHT RED
    {COLOR_GREEN, COLOR_GREEN}, // LIGHT GREEN
    {COLOR_YELLOW, COLOR_YELLOW}, // LIGHT YELLOW
    {COLOR_BLUE, COLOR_BLUE}, // LIGHT BLUE
    {COLOR_MAGENTA, COLOR_MAGENTA}, // LIGHT MAGENTA
    {COLOR_CYAN, COLOR_CYAN}, // LIGHT CYAN
    {COLOR_WHITE, COLOR_WHITE}, // WHITE
    {COLOR_BLACK, COLOR_BLACK}, // DEFAULT
    {COLOR_BLACK, COLOR_BLACK}, // BLACK
    {COLOR_RED, COLOR_BLACK}, // RED
    {COLOR_GREEN, COLOR_BLACK}, // GREEN
    {COLOR_YELLOW, COLOR_BLACK}, // YELLOW
    {COLOR_BLUE, COLOR_BLACK}, // BLUE
    {COLOR_MAGENTA, COLOR_BLACK}, // MAGENTA
    {COLOR_CYAN, COLOR_BLACK}, // CYAN
    {COLOR_WHITE, COLOR_BLACK}, // LIGHT GRAY
    {COLOR_BLACK, COLOR_BLACK}, // DARK GRAY
    {COLOR_RED, COLOR_BLACK}, // RED
    {COLOR_GREEN, COLOR_BLACK}, // GREEN
    {COLOR_YELLOW, COLOR_BLACK}, // YELLOW
    {COLOR_BLUE, COLOR_BLACK}, // BLUE
    {COLOR_MAGENTA, COLOR_BLACK}, // MAGENTA
    {COLOR_CYAN, COLOR_BLACK}, // CYAN
    {COLOR_WHITE, COLOR_BLACK} // WHITE
};

Arcade::Display::Ncurses::Ncurses()
    : ADisplayModule("Ncurses"), _events(SystemKeys::SYSKEYS_END, false), _currentColor(Colors::DEFAULT)
{
}

Arcade::Display::Ncurses::~Ncurses()
{
    endwin();
}

void Arcade::Display::Ncurses::reset()
{

}

void Arcade::Display::Ncurses::open()
{
    int i = 1;

    initscr();
    if (has_colors() == false) {
        endwin();
        throw Arcade::Exceptions::BadInstanciationException("This terminal does not have colors.", "Ncurses::open");
    }
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    timeout(1000 / 60);
    start_color();
    for (auto const &value : this->_colorsToInit) {
        init_pair(i, value.first, value.second);
        i++;
    }
}

bool Arcade::Display::Ncurses::isOpen() const
{
    return true;
}

bool Arcade::Display::Ncurses::switchToNextLib() const
{
    return this->_events.at(SystemKeys::F2);
}

bool Arcade::Display::Ncurses::switchToPreviousLib() const
{
    return this->_events.at(SystemKeys::F1);
}

bool Arcade::Display::Ncurses::switchToNextGame() const
{
    return this->_events.at(SystemKeys::F4);
}

bool Arcade::Display::Ncurses::switchToPreviousGame() const
{
    return this->_events.at(SystemKeys::F3);
}

bool Arcade::Display::Ncurses::shouldBeRestarted() const
{
    return this->_events.at(SystemKeys::R);
}

bool Arcade::Display::Ncurses::shouldGoToMenu() const
{
    return this->_events.at(SystemKeys::M);
}

bool Arcade::Display::Ncurses::shouldExit() const
{
    return this->_events.at(SystemKeys::ESCAPE);
}

bool Arcade::Display::Ncurses::isKeyPressed(IDisplayModule::Keys key) const
{
    return this->_events.at(key);
}

bool Arcade::Display::Ncurses::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return this->_events.at(key);
}

float Arcade::Display::Ncurses::getDelta() const
{
    return 1;
}

void Arcade::Display::Ncurses::clear() const
{
    wclear(stdscr);
}

void Arcade::Display::Ncurses::update()
{
    int key = getch();

    this->_keyCode = '\0';
    this->_events.assign(SystemKeys::SYSKEYS_END, false);
    if (key == ERR)
        return;
    this->_keyCode = key;
    auto found = std::find(this->_libKeys.begin(), this->_libKeys.end(), key);
    if (found != this->_libKeys.end())
        this->_events[std::distance(this->_libKeys.begin(), found)] = true;
}

void Arcade::Display::Ncurses::render() const
{
    refresh();
    usleep(90000);
}

char Arcade::Display::Ncurses::getKeyCode() const
{
    if (this->_keyCode == 263) // Equal to '\b'
        return '\b';
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

void Arcade::Display::Ncurses::setColor(IDisplayModule::Colors color)
{
    this->_currentColor = color;
}

void Arcade::Display::Ncurses::putPixel(float x, float y) const
{
    this->putRect(x, y, 1, 1);
}

void Arcade::Display::Ncurses::putLine(float x1, float y1, float x2, float y2) const
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float y = 0;

    for (float i = x1; i < x2; i++) {
        y = y1 + dy * (i - x1) / dx;
        this->putPixel(i, y);
    }
}

void Arcade::Display::Ncurses::putRect(float x, float y, float w, float h) const
{
    if (w < 32 || h < 32)
        return this->putFillRect(x, y, w, h);
    if (x < 0) {
        x *= -1;
        y *= -1;
        attron(COLOR_PAIR(this->_currentColor + 1));
        for (float i = 0; i <= w / 8; i++) {
            mvprintw(y / 16, x / 8 + i, "  ");
            mvprintw(y / 16 + h / 16, x / 8 + i, "  ");
        }
        for (float i = 0; i <= h / 16; i++) {
            mvprintw(y / 16 + i, x / 8, "  ");
            mvprintw(y / 16 + i, x / 8 + w / 8, "  ");
        }
        attroff(COLOR_PAIR(this->_currentColor + 1));
    } else if (x >= 0) {
        attron(COLOR_PAIR(this->_currentColor + 1));
        for (float i = 0; i <= w / 8; i++) {
            mvprintw(y / 16 + LINES / 2 - 10, x / 8 + i + COLS / 2 - 40, "  ");
            mvprintw(y / 16 + h / 16 + LINES / 2 - 10, x / 8 + i + COLS / 2 - 40, "  ");
        }
        for (float i = 0; i <= h / 16; i++) {
            mvprintw(y / 16 + i + LINES / 2 - 10, x / 8 + COLS / 2 - 40, "  ");
            mvprintw(y / 16 + i + LINES / 2 - 10, x / 8 + w / 8 + COLS / 2 - 40, "  ");
        }
        attroff(COLOR_PAIR(this->_currentColor + 1));
    }
}

void Arcade::Display::Ncurses::putFillRect(float x, float y, float w, float h) const
{
    if (x < 0) {
        x *= -1;
        y *= -1;
        attron(COLOR_PAIR(this->_currentColor + 1));
        for (float i = 0; i < h / 16; i++) {
            for (float j = 0; j < w / 8; j++) {
                mvprintw(y / 16, x / 8 + j, "  ");
            }
        }
        attroff(COLOR_PAIR(this->_currentColor + 1));
    }
    else if (x >= 0) {
        attron(COLOR_PAIR(this->_currentColor + 1));
        for (float i = 0; i < h / 16; i++) {
            for (float j = 0; j < w / 8; j++) {
                mvprintw(y / 16 + i + LINES / 2 - 10, x / 8 + j + COLS / 2 - 40, "  ");
            }
        }
        attroff(COLOR_PAIR(this->_currentColor + 1));
    }
}

void Arcade::Display::Ncurses::putCircle(float x, float y, float) const
{
    attr_t newColor = COLOR_PAIR(this->_currentColor + COLORS_END + 1);

    if (this->_currentColor + COLORS_END + 1 > 26)
        newColor |= A_BOLD;
    attron(newColor);
    if (x < 0) {
        x *= -1;
        y *= -1;
        mvprintw(y / 16, x / 8, "o");
    } else {
        mvprintw(y / 16 + LINES / 2 - 10, x / 8 + COLS / 2 - 40, "o");
    }
    attroff(newColor);
}

void Arcade::Display::Ncurses::putFillCircle(float x, float y, float ) const
{
    attr_t newColor = COLOR_PAIR(this->_currentColor + COLORS_END + 1);

    if (this->_currentColor + COLORS_END + 1 > 26)
        newColor |= A_BOLD;
    attron(newColor);
    if (x < 0) {
        x *= -1;
        y *= -1;
        mvprintw(y / 16, x / 8, "o");
    } else {
        mvprintw(y / 16 + LINES / 2 - 10, x / 8 + COLS / 2 - 40, "o");
    }
    attroff(newColor);
}

void Arcade::Display::Ncurses::putText(const std::string &text, unsigned int, float x, float y) const
{
    attr_t newColor = COLOR_PAIR(this->_currentColor + COLORS_END + 1);

    if (this->_currentColor + COLORS_END + 1 > 26)
        newColor |= A_BOLD;
    if (x < 0) {
        x *= -1;
        y *= -1;
        attron(newColor);
        mvprintw(y / 16, x / 8, text.c_str());
        attroff(newColor);
    } else if (x >= 0) {
        attron(newColor);
        mvprintw(y / 16 + LINES / 2 - 10, x / 8 + COLS / 2 - 40, text.c_str());
        attroff(newColor);
    }
}
