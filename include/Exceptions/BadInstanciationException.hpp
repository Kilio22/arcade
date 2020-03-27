/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** BadInstanciation
*/

#ifndef BADINSTANCIATION_HPP_
#define BADINSTANCIATION_HPP_

#include "Exceptions/ArcadeException.hpp"

namespace Arcade::Exceptions
{
    /**
     * @brief Thrown when library objects failed to be instanciated.
     */
    class BadInstanciationException : public ArcadeException
    {
        public:
            /**
             * @brief Construct a new Bad Instanciation Exception object
             * @param message Message explaining the problem.
             * @param component Additional information on where the problem occured.
             */
            BadInstanciationException(std::string const &message, std::string const &component);
            ~BadInstanciationException() = default;
    };
}

#endif /* !BADINSTANCIATION_HPP_ */
