/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "lib/DataStructures.h"
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
            std::vector<rectangle_t> _rects;
            std::vector<circle_t> _cicles;
            std::vector<circle_t> _monsters;
            std::vector<circle_t> _pacman;
    };
}

#endif /* !PACMAN_HPP_ */
