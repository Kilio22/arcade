/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Qix
*/

#ifndef QIX_HPP_
#define QIX_HPP_

#include "games/AGameModule.hpp"

namespace Arcade::Games
{
    class Qix : public AGameModule
    {
        public:
            Qix();
            ~Qix() = default;

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;

        private:
    };
}

#endif /* !QIX_HPP_ */
