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

            bool loadFromFile(const std::string &filepath = "") final;

            bool saveToFile(const std::string &filepath = "") const final;

            void setPlayerName(const std::string &name) final;
            std::tuple<std::string, int> getHighscore() const final;
            std::vector<std::tuple<std::string, int>> getLatestScores() const final;

            const std::string &getLibName() const final;

        protected:
        private:
            std::string _playerName;
            std::string _libName;
            std::vector<std::tuple<std::string, int>> _highscores;

            static const std::regex highscoreRegex;
    };
}


#endif /* !AGAMEMODULE_HPP_ */
