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
#include "DLInfos.h"
#include "games/IGameModule.hpp"
#include "lib/IDisplayModule.hpp"

/** \namespace Arcade
 *  Default namespace for the project.
 */
namespace Arcade
{
    /**
     * @brief Core class that handles all the interactions between the library modules and the game modules.
     */
    class Core
    {
        private:
            enum Direction
            {
                PREV = 0,
                NEXT = 1
            };

        public:
            /**
             * @brief Construct a new Core object
             * @param startLibraryPath The library path that will be first used when the program will be started.
             */
            explicit Core(const std::string &startLibraryPath);
            ~Core() = default;

            /**
             * @brief Starts the arcade program.
             */
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

            std::vector<DLInfos> libraries;
            int iLib;
            std::vector<DLInfos> games;
            int iGame;

            std::unique_ptr<Display::IDisplayModule> displayModule;
            std::unique_ptr<Games::IGameModule> gameModule;
    };
}

#endif /* !CORE_HPP_ */
