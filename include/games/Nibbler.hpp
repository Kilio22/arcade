/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "games/AGameModule.hpp"
#include <list>

namespace Arcade::Games
{
    /**
     * @brief Nibbler game
     */
    class Nibbler : public AGameModule
    {
        private:
            enum Direction
            {
                LEFT,
                RIGHT,
                UP,
                DOWN
            };

        public:
            Nibbler();
            ~Nibbler() = default;

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &displayModule) final;

            /**
             * @brief Renders the Nibbler game on the display module.
             * @param displayModule The display module that will be used to put things on a canvas.
             */
            void render(Arcade::Display::IDisplayModule &displayModule) const final;

        private:
            const int xTiles = 40;
            const int yTiles = 29;
            const int xSize = WIDTH / xTiles;
            const int ySize = HEIGHT / yTiles;

            void spawnFruit();
            bool isDead();

            void updateDirection(const Arcade::Display::IDisplayModule &displayModule);
            void updateSnake();

            void drawBorder(Arcade::Display::IDisplayModule &displayModule) const;
            void drawFruit(Arcade::Display::IDisplayModule &displayModule) const;
            void drawSnake(Arcade::Display::IDisplayModule &displayModule) const;
            void drawControls(Arcade::Display::IDisplayModule &displayModule) const;

            float framesToStep;
            float frameCount;
            Direction direction;
            Direction lastDirection;
            std::pair<int, int> fruit;
            std::list<std::pair<int, int>> snake;
    };
}

#endif /* !NIBBLER_HPP_ */
