/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "DataStructures.h"
#include "time.h"
#include "games/AGameModule.hpp"

namespace Arcade::Games
{
    /**
     * @brief Pacman game
     */
    class Pacman : public AGameModule
    {
        public:
            Pacman();
            ~Pacman();

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;

            /**
             * @brief Renders the Pacman game on the display module.
             * @param displayModule The display module that will be used to put things on a canvas.
             */
            void render(Arcade::Display::IDisplayModule &lib) const final;

        private:
            enum Direction
            {
                LEFT,
                RIGHT,
                UP,
                DOWN
            };

            void drawMaze(Arcade::Display::IDisplayModule &displayModule) const;
            void drawMonsters(Arcade::Display::IDisplayModule &displayModule) const;
            void initMaze(void);
            void initEntities(void);
            void updatePacmanDirection(const Arcade::Display::IDisplayModule &displayModule);
            bool canMove(const float x, const float y) const;
            bool isDead(void);
            void eat(void);
            void moveMonsters(void);
            bool moveEntity(std::pair<circle_t, Direction> &entity) const;
            void moveRandomDirection(std::pair<circle_t, Direction> &monster) const;
            void generateMonsters(void);
            void generateTokens(void);

            std::vector<rectangle_t> _walls;
            std::vector<rectangle_t> _path;
            std::vector<std::pair<rectangle_t, rectangle_t>> _bonuses;
            std::vector<std::pair<rectangle_t, circle_t>> _tokens;
            std::vector<std::pair<circle_t, Pacman::Direction>> _monsters;
            std::pair<circle_t, Pacman::Direction> _pacman;
            clock_t _eatClock;
            int _framesToStep;
            int _framesCount;
            bool _canEatMonsters;

            static const std::string _mapPath;
            static const std::vector<std::tuple<float, float, Display::IDisplayModule::Colors>> _monstersPositions;
    };
}

#endif /* !PACMAN_HPP_ */
