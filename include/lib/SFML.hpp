/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include "IDisplayModule.hpp"

namespace Arcade::Display
{
    /**
     * @brief SFML library
     */
    class SFML : public IDisplayModule
    {
        public:
            SFML();
            ~SFML();

            void reset() final;
            void open() final;
            bool isOpen() const final;

            bool switchToNextLib() const final;
            bool switchToPreviousLib() const final;
            bool switchToNextGame() const final;
            bool switchToPreviousGame() const final;

            bool shouldBeRestarted() const final;
            bool shouldGoToMenu() const final;
            bool shouldExit() const final;

            bool isKeyPressed(IDisplayModule::Keys) const final;
            bool isKeyPressedOnce(IDisplayModule::Keys) const final;
            float getDelta() const final;

            void clear() const final;
            void update() final;
            void render() const final;

            char getKeyCode() const final;

            void setColor(IDisplayModule::Colors col) final;
            void putPixel(float x, float y) const final;
            void putLine(float x1, float y1, float x2, float y2) const final;
            void putRect(float x, float y, float w, float h) const final;
            void putFillRect(float x, float y, float w, float h) const final;
            void putCircle(float x, float y, float rad) const final;
            void putFillCircle(float x, float y, float rad) const final;
            void putText(const std::string &text, unsigned int size, float x, float y) const final;

            const std::string &getLibName() const final;

        private:
            std::unique_ptr<sf::RenderWindow> _window;
            Colors _currentColor;
            std::vector<bool> _events;
            char _keyCode;
            std::unique_ptr<sf::Font> _font;

            static const std::string _libName;
            static const std::vector<sf::Color> _libColors;
            static const std::vector<sf::Keyboard::Key> _libKeys;
    };
}

#endif /* !SFML_HPP_ */
