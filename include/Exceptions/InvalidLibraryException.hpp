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
    /**
     * @brief Thrown when trying to use an invalid library file.
     */
    class InvalidLibraryException : public ArcadeException
    {
        public:
            /**
             * @brief Construct a new Invalid Library Exception object
             * @param message Message explaining the problem.
             * @param component Additional information on where the problem occured.
             */
            InvalidLibraryException(std::string const &message, std::string const &component);
            ~InvalidLibraryException() = default;
    };
}

#endif /* !INVALIDLIBRARYEXCEPTION_HPP_ */
