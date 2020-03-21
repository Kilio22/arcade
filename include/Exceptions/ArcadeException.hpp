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

namespace Arcade::Exceptions
{
    class ArcadeException : public std::runtime_error
    {
        public:
            ArcadeException(std::string const &message, std::string const &component);
            ~ArcadeException() = default;

            std::string const &getComponent(void) const noexcept;

        protected:
        private:
            std::string _message;
            std::string _component;
    };
}


#endif /* !ARCADEEXCEPTION_HPP_ */
