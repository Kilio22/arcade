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
             * @param libname THe library's name
             */
            AGameModule(std::string const &libname);
            virtual ~AGameModule();

            bool loadFromFile(const std::string &filepath) final;
            bool loadFromFile() final;

            bool saveToFile(const std::string &filepath) const final;
            bool saveToFile() const final;

            void setPlayerName(const std::string &name) final;
            std::pair<std::string, int> getScore() const final;
            std::vector<std::pair<std::string, int>> getBestScores() const final;

            /**
             * Default game implementation
             * (out of order)
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
            void displayGameOver(Arcade::Display::IDisplayModule &displayModule) const;

            /**
             * @brief The current score of the active game session
             */
            int _currentScore;
            bool _isDead;

        private:
            std::string _playerName;
            std::string _libName;
            std::vector<std::pair<std::string, int>> _highscores;

            static const std::regex highscoreRegex;

            void sortHighscores(void);
    };
}


#endif /* !AGAMEMODULE_HPP_ */
