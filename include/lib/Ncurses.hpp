/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <memory>
#include <curses.h>
#include "ADisplayModule.hpp"

namespace Arcade::Display
{
    /**
     * @brief Libncurses library
     */
    class Ncurses : public ADisplayModule
    {
        public:
            Ncurses();
            ~Ncurses();

            void reset() final;
            void open() final;
            void close() final;
            bool isOpen() const final;

            bool switchToNextLib() const final;
            bool switchToPreviousLib() const final;
            bool switchToNextGame() const final;
            bool switchToPreviousGame() const final;

            bool shouldBeRestarted() const final;
            bool shouldGoToMenu() const final;
            bool shouldExit() const final;

            bool isKeyPressed(IDisplayModule::Keys key) const final;
            bool isKeyPressedOnce(IDisplayModule::Keys key) const final;
            float getDelta() const final;

            void clear() const final;
            void update() final;
            void render() const final;

            char getKeyCode() const final;

            void setColor(IDisplayModule::Colors color) final;
            void putPixel(float x, float y) const final;
            void putLine(float x1, float y1, float x2, float y2) const final;
            void putRect(float x, float y, float w, float h) const final;
            void putFillRect(float x, float y, float w, float h) const final;
            void putCircle(float x, float y, float rad) const final;
            void putFillCircle(float x, float y, float rad) const final;
            void putText(const std::string &text, unsigned int size, float x, float y) const final;

        private:
            std::vector<bool> _events;
            int _keyCode;
            Colors _currentColor;

            static const std::vector<int> _libKeys;
            static const std::vector<std::pair<int, int>> _colorsToInit;
    };
}

#endif /* !NCURSES_HPP_ */
