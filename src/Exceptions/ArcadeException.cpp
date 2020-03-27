/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeException
*/

#include "Exceptions/ArcadeException.hpp"

Arcade::Exceptions::ArcadeException::ArcadeException(std::string const &message, std::string const &component)
    : _message(message), _component(component)
{
}

std::string const &Arcade::Exceptions::ArcadeException::getComponent(void) const noexcept
{
    return this->_component;
}

const char *Arcade::Exceptions::ArcadeException::what(void) const noexcept
{
    return this->_message.c_str();
}