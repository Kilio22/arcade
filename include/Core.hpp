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

namespace Arcade
{
    class Core
    {
        public:
            Core();
            ~Core();

        private:
            std::string _username;
            std::vector<std::string> libraries;
            std::vector<std::string> games;
    };
}

#endif /* !CORE_HPP_ */
