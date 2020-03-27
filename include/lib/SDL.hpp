/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include "ADisplayModule.hpp"

namespace Arcade::Display
{
    /**
     * @brief SDL library
     */
    class SDL : public ADisplayModule
    {
        public:
            SDL();
            ~SDL();

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

            bool isKeyPressed(IDisplayModule::Keys key) const final;
            bool isKeyPressedOnce(IDisplayModule::Keys key) const final;
            float getDelta() const final;

            void clear() const final;
            void update() final;
            void render() const final;

            char getKeyCode() const final;

            void setColor(IDisplayModule::Colors color) final;
            void putPixel(float x, float y) const final;
            void putLine(float x1, float y1, float x2, float y2) const final;
            void putRect(float x, float y, float w, float h) const final;
            void putFillRect(float x, float y, float w, float h) const final;
            void putCircle(float x, float y, float rad) const final;
            void putFillCircle(float x, float y, float rad) const final;
            void putText(const std::string &text, unsigned int size, float x, float y) const final;

        private:
            SDL_Window *_window;
            SDL_Surface *_surface;
            SDL_Renderer *_renderer;
            std::unique_ptr<std::map<unsigned int, TTF_Font *>> _fonts;
            Colors _currentColor;
            std::vector<bool> _events;
            char _keyCode;

            static const std::vector<SDL_Keycode> _libKeys;
            static const std::vector<SDL_Color> _libColors;
            static const std::string _libName;
    };
}

#endif /* !SDL_HPP_ */
