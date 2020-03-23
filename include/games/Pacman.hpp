/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

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

        protected:
        private:
    };
}

#endif /* !PACMAN_HPP_ */
