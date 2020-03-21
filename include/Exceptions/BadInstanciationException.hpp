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
    class BadInstanciationException : public ArcadeException
    {
        public:
            BadInstanciationException(std::string const &message, std::string const &component);
            ~BadInstanciationException() = default;

        protected:
        private:
    };
}


#endif /* !BADINSTANCIATION_HPP_ */
