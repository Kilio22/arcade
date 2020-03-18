/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeException
*/

#ifndef ARCADEEXCEPTION_HPP_
#define ARCADEEXCEPTION_HPP_

#include <exception>
#include <string>

namespace Arcade::Exceptions
{
    class ArcadeException : public std::exception
    {
        public:
            ArcadeException(std::string const &message, std::string const &component);
            ~ArcadeException() = default;

            const char *what(void) const noexcept;
            std::string const &getComponent(void) const noexcept;

        protected:
        private:
            std::string _message;
            std::string _component;
    };
}


#endif /* !ARCADEEXCEPTION_HPP_ */
