/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include "games/AGameModule.hpp"

namespace Arcade::Games
{
    /**
     * @brief Centipede game
     */
    class Centipede : public AGameModule
    {
        public:
            Centipede();
            ~Centipede() = default;

            void reset() final;

            void update(const Arcade::Display::IDisplayModule &lib) final;

        private:
    };
}

#endif /* !CENTIPEDE_HPP_ */
