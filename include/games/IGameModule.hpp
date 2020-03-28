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
#include "lib/IDisplayModule.hpp"

#define SAVE_PATH "./games/.saves/"

/** \namespace Arcade::Games
 *  Contains elements related to the game libraries of the Arcade project.
 */
namespace Arcade::Games
{
    /**
     * @brief Interface for the game modules used to handle games.
     */
    class IGameModule
    {
        public:
            virtual ~IGameModule() = default;


            /**
             * @brief Resets and restarts the game
             */
            virtual void reset() = 0;


            /**
             * @brief Loads highscores from a file
             * @param filepath The file path
             * @return true Highscores were loaded
             * @return false An error occured
             */
            virtual bool loadFromFile(const std::string &filepath) = 0;

            /**
             * @brief Loads highscores from the default save file
             * @return true Highscores were loaded
             * @return false An error occured
             */
            virtual bool loadFromFile() = 0; // default filename


            /**
             * @brief Saves highscores to a file
             * @param filepath The file path
             * @return true Highscores were saved
             * @return false An error occured
             */
            virtual bool saveToFile(const std::string &filepath) const = 0;

            /**
             * @brief Saves highscores from the default save file
             * @return true Highscores were saved
             * @return false An error occured
             */
            virtual bool saveToFile() const = 0; // default filename


            /**
             * @brief Sets the player name
             * @param name The player name
             */
            virtual void setPlayerName(const std::string &name) = 0;

            /**
             * @brief Gets the current score
             * @return std::pair<std::string, int> [Name, score] value pairs
             */
            virtual std::pair<std::string, int> getScore() const = 0;

            /**
             * @brief Gets the best 16 scores
             * @return std::vector<std::pair<std::string, int>> Vector of [name, score] value pairs
             */
            virtual std::vector<std::pair<std::string, int>> getBestScores() const = 0;


            /**
             * @brief Updates the game
             * @param lib The display module that will be used to get events that occured
             */
            virtual void update(const Arcade::Display::IDisplayModule &lib) = 0;

            /**
             * @brief Renders the game on the display module.\n
             * THIS MUST ONLY DRAW THINGS ON THE CANVAS, so don't call the Arcade::Display::IDisplayModule::update or Arcade::Display::IDisplayModule::render methods.
             *
             * @param lib The display module that will be used to put things on a canvas.
             */
            virtual void render(Arcade::Display::IDisplayModule &lib) const = 0;


            /**
             * @brief Gets the library name
             * @return The library's name
             */
            virtual const std::string &getLibName() const = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
