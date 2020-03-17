/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <string>
#include <tuple>
#include <vector>
#include "IDisplayModule.hpp"

namespace Arcade::Games
{
    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            // For the core

            // Reset game at any moment
            virtual void reset() = 0;

            // Load highscores from file and return wether it worked or not
            virtual bool loadFromFile(std::string filepath) = 0; // with filename
            virtual bool loadFromFile() = 0; // default filename

            // save highscores to file return wether it worked or not
            virtual bool saveToFile(std::string filepath) = 0; // with filename
            virtual bool saveToFile() = 0; // default filename

            // Set the player's name
            virtual void setPlayerName(std::string) = 0;
            // get the best score
            virtual std::tuple<std::string, int> getHighscore() = 0;
            // get the 16 best scores
            virtual std::vector<std::tuple<std::string, int>> getLatestScores() = 0;

            // Handle Game
            // update game
            virtual void update() = 0;
            // display stuff using the lib given as an argument.
            virtual void render(Arcade::Display::IDisplayModule &lib) = 0;
            virtual std::string getGameName() const = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
