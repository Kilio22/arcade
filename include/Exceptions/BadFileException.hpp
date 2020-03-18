/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** BadFileException
*/

#ifndef BADFILEEXCEPTION_HPP_
#define BADFILEEXCEPTION_HPP_

#include "ArcadeException.hpp"

namespace Arcade::Exceptions
{
    class BadFileException : public Arcade::Exceptions::ArcadeException
    {
        public:
            BadFileException(std::string const &message, std::string const &component);
            ~BadFileException() = default;

        protected:
        private:
    };
}

#endif /* !BADFILEEXCEPTION_HPP_ */
