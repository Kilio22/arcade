/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include <fstream>
#include <regex>
#include "games/IGameModule.hpp"

namespace Arcade::Games
{
    /**
     * @brief Abstract class implementing key methods of the IGameModule interface
     */
    class AGameModule : public IGameModule
    {
        public:
            /**
             * @brief Construct a new AGameModule object
             * @param libName The library's name
             */
            AGameModule(std::string const &libName);
            virtual ~AGameModule();

            bool loadFromFile(const std::string &filepath) final;
            bool loadFromFile() final;

            bool saveToFile(const std::string &filepath) const final;
            bool saveToFile() const final;

            void setPlayerName(const std::string &name) final;
            std::pair<std::string, int> getScore() const final;
            std::vector<std::pair<std::string, int>> getBestScores() const final;

            /**
             * @brief Default game implementation (out of order)
             * @param lib The display module that will be used to put things on a canvas.
             */
            void render(Arcade::Display::IDisplayModule &lib) const override;

            const std::string &getLibName() const final;

        protected:
            /**
             * @brief Adds a score to the scoreboard
             * @param nb The score value
             */
            void addToBestScores(int nb);

            /**
             * @brief Display game over screen
             * @param displayModule The display module
             */
            void drawGameOver(Arcade::Display::IDisplayModule &displayModule) const;

            int _currentScore; ///< The current score of the active game session
            bool _isDead; ///< True if the player is dead

        private:
            std::string _playerName;
            std::string _libName;
            std::vector<std::pair<std::string, int>> _highscores;

            static const std::regex highscoreRegex;

            void sortHighscores(void);
    };
}


#endif /* !AGAMEMODULE_HPP_ */
