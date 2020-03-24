/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <vector>
#include "games/IGameModule.hpp"
#include "lib/IDisplayModule.hpp"

namespace Arcade
{
    class Core
    {
        private:
            enum Direction
            {
                PREV = 0,
                NEXT = 1
            };

        public:
            explicit Core(const std::string &startLibraryPath);
            ~Core() = default;

            void play();

        private:
            void displayOverlay() const;
            void displayControls() const;

            void menuEvents();
            void menuDisplay() const;

            void gameEvents();
            void gameDisplay() const;

            void switchLibrary(Direction direction);
            void switchGame(Direction direction);

            std::string username;

            std::vector<std::pair<std::string, std::string>> libraries;
            int iLib;
            std::vector<std::pair<std::string, std::string>> games;
            int iGame;

            std::unique_ptr<Display::IDisplayModule> displayModule;
            std::unique_ptr<Games::IGameModule> gameModule;
    };
}

#endif /* !CORE_HPP_ */
