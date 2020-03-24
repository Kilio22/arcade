/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Solarfox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include "games/AGameModule.hpp"

namespace Arcade::Games
{
    class Solarfox : public AGameModule
    {
        public:
            Solarfox();
            ~Solarfox() = default;

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;

        private:
    };
}

#endif /* !SOLARFOX_HPP_ */
