/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeException
*/

#ifndef ARCADEEXCEPTION_HPP_
#define ARCADEEXCEPTION_HPP_

#include <stdexcept>
#include <string>

/** \namespace Arcade::Exceptions
 *  Contains a loadout of exceptions that are used in the Arcade project.
 */
namespace Arcade::Exceptions
{
    /**
     * @brief Base exception class for this projects' exceptions
     */
    class ArcadeException : public std::runtime_error
    {
        public:
            /**
             * @brief Construct a new Arcade Exception object
             * @param message Message explaining the problem.
             * @param component Additional information on where the problem occured.
             */
            ArcadeException(std::string const &message, std::string const &component);
            ~ArcadeException() = default;

            /**
             * @brief Gets the name of component where the exception occured.
             * @return The component name
             */
            std::string const &getComponent(void) const noexcept;

        private:
            std::string _message;
            std::string _component;
    };
}

#endif /* !ARCADEEXCEPTION_HPP_ */
