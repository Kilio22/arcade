/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** InvalidLibraryException
*/

#ifndef INVALIDLIBRARYEXCEPTION_HPP_
#define INVALIDLIBRARYEXCEPTION_HPP_

#include "ArcadeException.hpp"

namespace Arcade::Exceptions
{
    class InvalidLibraryException : public ArcadeException
    {
        public:
            InvalidLibraryException(std::string const &message, std::string const &component);
            ~InvalidLibraryException() = default;
    };
}

#endif /* !INVALIDLIBRARYEXCEPTION_HPP_ */
