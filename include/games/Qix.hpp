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
            ~Qix();

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;
            void render(Arcade::Display::IDisplayModule &lib) const final;

        private:
    };
}

#endif /* !QIX_HPP_ */
