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
    class AGameModule : public IGameModule
    {
        public:
            AGameModule(std::string const &libname);
            virtual ~AGameModule() = default;

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
            void addToBestScores(int nb);
            int _currentScore;
        private:
            std::string _playerName;
            std::string _libName;
            std::vector<std::pair<std::string, int>> _highscores;

            static const std::regex highscoreRegex;
    };
}


#endif /* !AGAMEMODULE_HPP_ */
