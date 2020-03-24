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
            ~Nibbler() = default;

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;

        private:
    };
}

#endif /* !NIBBLER_HPP_ */
