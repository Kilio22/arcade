/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <memory>
#include "IDisplayModule.hpp"

namespace Arcade::Display
{
    class NCurses : public IDisplayModule
    {
        public:
            NCurses();
            ~NCurses();

            void reset() final;
            bool isOpen() final;

            bool switchToNext_lib() final;
            bool switchToPrevious_lib() final;
            bool switchToNext_game() final;
            bool switchToPrevious_game() final;

            bool shouldBeRestarted() final;
            bool shouldGoToMenu() final;
            bool shouldExit() final;

            bool isKeyPressed(IDisplayModule::Keys) final;
            bool isKeyPressedOnce(IDisplayModule::Keys) final;

            float getDelta() final;

            void clear() final;
            void update() final;
            void render() final;

            std::string getPlayerName() final;
            void setPlayerName(std::string) final;

            void setColor(IDisplayModule::Colors col) final;
            void putPixel(float x, float y) final;
            void putLine(float x1, float y1, float x2, float y2) final;
            void putRect(float x, float y, float w, float h) final;
            void putFillRect(float x, float y, float w, float h) final;
            void putCircle(float x, float y, float rad) final;
            void putFillCircle(float x, float y, float rad) final;
            void putText(std::string text, float size, float x, float y) final;

            std::string getLibName() const final;

        protected:
        private:
    };
}

#endif /* !NCURSES_HPP_ */
