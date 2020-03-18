/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <memory>
#include "IDisplayModule.hpp"

namespace Arcade::Display
{
    class SFML : public IDisplayModule
    {
        public:
            SFML();
            ~SFML();

            void reset() final;
            bool isOpen() final;

            bool switchToNext_lib() final;
            bool switchToPrevious_lib() final;
            bool switchToNext_game() final;
            bool switchToPrevious_game() final;

            bool shouldBeRestarted() final;
            bool shouldGoToMenu() final;
            bool shouldExit() final;

            bool isKeyPressed(Keys key) final;
            bool isKeyPressedOnce(Keys key) final;

            float getDelta() final;

            void clear() final;
            void update() final;
            void render() final;

            const std::string &getPlayerName() final;
            void setPlayerName(const std::string &name) final;

            void setColor(Colors color) final;
            void putPixel(float x, float y) final;
            void putLine(float x1, float y1, float x2, float y2) final;
            void putRect(float x, float y, float w, float h) final;
            void putFillRect(float x, float y, float w, float h) final;
            void putCircle(float x, float y, float rad) final;
            void putFillCircle(float x, float y, float rad) final;
            void putText(const std::string &text, float size, float x, float y) final;

            const std::string &getLibName() const final;

        protected:
        private:
    };
}

#endif /* !SFML_HPP_ */
