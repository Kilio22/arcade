/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLInfos
*/

#ifndef DLINFOS_H_
#define DLINFOS_H_

#include <string>
#include <vector>

namespace Arcade
{
    /**
     * @brief Contains information about a given library
     */
    struct DLInfos
    {
        std::string path; ///< Path of the library

        /**
         * @brief Name of the library \n
         * <em>(Arcade::Games::IGameModule::getLibName or Arcade::Display::IDisplayModule::getLibName)</em>
         */
        std::string name;

        /**
         * @brief For Arcade::Games::IGameModule, vector containing the best scores <em>(obtained by Arcade::Games::IGameModule::getBestScores)</em>. \n
         * For Arcade::Display::IDisplayModule, <b>empty vector</b>.
         */
        std::vector<std::pair<std::string, int>> scores;
    };
}

#endif /* !DLINFOS_H_ */
