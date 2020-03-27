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
    /**
     * @brief Thrown when looking up to an external file that is inexistant.
     */
    class BadFileException : public Arcade::Exceptions::ArcadeException
    {
        public:
            /**
             * @brief Construct a new Bad File Exception object
             * @param message Message explaining the problem.
             * @param component Additional information on where the problem occured.
             */
            BadFileException(std::string const &message, std::string const &component);
            ~BadFileException() = default;
    };
}

#endif /* !BADFILEEXCEPTION_HPP_ */
