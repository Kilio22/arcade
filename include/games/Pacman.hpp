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
    class Pacman : public AGameModule
    {
        public:
            Pacman();
            ~Pacman();

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;
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
            void updateDirection(const Arcade::Display::IDisplayModule &displayModule);
            void move(void);
            bool canMove(float x, float y);
            bool isDead(void);
            void eat(void);
            void moveMonsters(void);

            std::vector<rectangle_t> _walls;
            std::vector<rectangle_t> _path;
            std::vector<std::pair<rectangle_t, rectangle_t>> _bonuses;
            std::vector<std::pair<rectangle_t, circle_t>> _tokens;
            std::vector<circle_t> _monsters;
            circle_t _pacman;
            Direction _direction;
            bool _canEatMonsters;
            clock_t _eatClock;
            int _framesToStep;
            int _framesCount;
            static const std::string _mapPath;
    };
}

#endif /* !PACMAN_HPP_ */
