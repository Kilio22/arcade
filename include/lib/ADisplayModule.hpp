/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ADisplayModule
*/

#ifndef ADISPLAYMODULE_HPP_
#define ADISPLAYMODULE_HPP_

#include "IDisplayModule.hpp"

namespace Arcade::Display
{
    /**
     * @brief Abstract class adding utilities and an enum to the IDisplayModule interface
     */
    class ADisplayModule : public IDisplayModule
    {
        protected:
            /**
             * @brief Additional keys that are used by the library
             */
            enum SystemKeys
            {
                ESCAPE = Keys::KEYS_END,
                M,
                R,
                F1,
                F2,
                F3,
                F4,
                SYSKEYS_END
            };

        public:
            /**
             * @brief Construct a new ADisplayModule object
             * @param libName The library's name
             */
            ADisplayModule(const std::string &libName);
            virtual ~ADisplayModule() = default;

            const std::string &getLibName() const final;

        private:
            std::string libName;
    };
}

#endif /* !ADISPLAYMODULE_HPP_ */
