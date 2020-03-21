/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeException
*/

#include "Exceptions/ArcadeException.hpp"

Arcade::Exceptions::ArcadeException::ArcadeException(std::string const &message, std::string const &component)
    : std::runtime_error(message), _component(component)
{
}

std::string const &Arcade::Exceptions::ArcadeException::getComponent(void) const noexcept
{
    return this->_component;
}
