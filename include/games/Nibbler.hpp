/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "games/AGameModule.hpp"

namespace Arcade::Games
{
    class Nibbler : public AGameModule
    {
        public:
            Nibbler();
            ~Nibbler();

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;
            void render(Arcade::Display::IDisplayModule &lib) const final;

        private:
    };
}

#endif /* !NIBBLER_HPP_ */
