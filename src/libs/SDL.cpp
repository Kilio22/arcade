/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#include <functional>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include "lib/SDL.hpp"
#include "Exceptions/BadInstanciationException.hpp"
#include "Exceptions/BadFileException.hpp"

const std::vector<SDL_Scancode> Arcade::Display::SDL::_libKeys =
{
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_A,
    SDL_SCANCODE_E,
    SDL_SCANCODE_W,
    SDL_SCANCODE_X,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_J,
    SDL_SCANCODE_K,
    SDL_SCANCODE_U,
    SDL_SCANCODE_I,
    SDL_SCANCODE_M,
    SDL_SCANCODE_R
};

const std::vector<SDL_Color> Arcade::Display::SDL::_libColors =
{
    {255, 255, 255, 255},
    {0, 0, 0, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {255, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 0, 255, 255},
    {0, 255, 255, 255},
    {128, 128, 128, 255},
    {105, 105, 105, 255},
    {255, 0, 0, 255},
    {0, 255, 111, 255},
    {255, 255, 0, 255},
    {0, 162, 255, 255},
    {255, 0, 247, 255},
    {0, 247, 255, 255},
    {0, 0, 0, 255}
};

const std::string Arcade::Display::SDL::_libName = "SDL";

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SDL>();
}

Arcade::Display::SDL::SDL()
    : _window(nullptr), _currentColor(Colors::DEFAULT), _events(20, false), _keyCode('\0')
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        throw Arcade::Exceptions::BadInstanciationException(std::string("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError())), "SDL Ctor");
    }
    this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (this->_window == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Window creation failed.", "SDL Ctor");
    }
    this->_surface = SDL_GetWindowSurface(this->_window);
    if (this->_surface == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Surface creation failed.", "SDL Ctor");
    }
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Renderer creation failed.", "SDL Ctor");
    }
    SDL_StartTextInput();
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255); // set to current color
}

Arcade::Display::SDL::~SDL()
{
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
    TTF_Quit();
    SDL_Quit();
}

void Arcade::Display::SDL::reset()
{}

bool Arcade::Display::SDL::isOpen() const
{
    return true;
}

bool Arcade::Display::SDL::switchToNextLib() const
{
    return this->_events.at(Keys::RIGHT);
}

bool Arcade::Display::SDL::switchToPreviousLib() const
{
    return this->_events.at(Keys::LEFT);
}

bool Arcade::Display::SDL::switchToNextGame() const
{
    return this->_events.at(Keys::UP);
}

bool Arcade::Display::SDL::switchToPreviousGame() const
{
    return this->_events.at(Keys::DOWN);
}

bool Arcade::Display::SDL::shouldBeRestarted() const
{
    return this->_events.at(Keys::R);
}

bool Arcade::Display::SDL::shouldGoToMenu() const
{
    return this->_events.at(Keys::M);
}

bool Arcade::Display::SDL::shouldExit() const
{
    return this->_events.at(Keys::ESCAPE);
}

bool Arcade::Display::SDL::isKeyPressed(IDisplayModule::Keys key) const
{
    return this->_events.at(key);
}

bool Arcade::Display::SDL::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return this->_events.at(key);
}

float Arcade::Display::SDL::getDelta() const
{
    return 1;
}

void Arcade::Display::SDL::clear() const
{
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255); // set to black
    SDL_RenderClear(this->_renderer); // clear window
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255); // set to current color
}

void Arcade::Display::SDL::update()
{
    SDL_Event event;

    this->_events.assign(Keys::KEYS_END, false);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            auto found = std::find(this->_libKeys.begin(), this->_libKeys.end(), event.key.keysym.scancode);
            if (found != this->_libKeys.end()) {
                this->_events[std::distance(this->_libKeys.begin(), found)] = true;
            }
        }
        if (event.type == SDL_TEXTINPUT) {
            std::cout << event.text.text << std::endl;
            this->_keyCode = event.text.text[0];
            memset(event.text.text, '\0', SDL_TEXTINPUTEVENT_TEXT_SIZE);
        }
    }
}

void Arcade::Display::SDL::render() const
{
    SDL_RenderPresent(this->_renderer);
}

char Arcade::Display::SDL::getKeyCode() const
{
    if (this->_keyCode == '\b')
        return '\b';
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

void Arcade::Display::SDL::setColor(IDisplayModule::Colors color)
{
    this->_currentColor = color;
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255);
}

void Arcade::Display::SDL::putPixel(float x, float y) const
{
    this->putRect(x, y, 1, 1);
}

void Arcade::Display::SDL::putLine(float x1, float y1, float x2, float y2) const
{
    SDL_RenderDrawLine(this->_renderer, x1, y1, x2, y2);
}

void Arcade::Display::SDL::putRect(float x, float y, float w, float h) const
{
    SDL_Rect fillRect = {(int)x, (int)y, (int)w, (int)h};

    SDL_RenderDrawRect(this->_renderer, &fillRect);
}

void Arcade::Display::SDL::putFillRect(float x, float y, float w, float h) const
{
    SDL_Rect fillRect = {(int)x, (int)y, (int)w, (int)h};

    SDL_RenderFillRect(this->_renderer, &fillRect);
}

void Arcade::Display::SDL::putCircle(float x, float y, float radius) const
{
    int pk = 1 - radius;
    int px = 0;
    int py = radius;
    int oldPx = 0;
    int oldPy = radius;

    x += radius;
    y += radius;
    while (py > px) {
        SDL_RenderDrawPoint(this->_renderer, x + px, y + py);
        SDL_RenderDrawPoint(this->_renderer, x + px, y - py);
        SDL_RenderDrawPoint(this->_renderer, x - px, y - py);
        SDL_RenderDrawPoint(this->_renderer, x - px, y + py);
        SDL_RenderDrawPoint(this->_renderer, x + py, y + px);
        SDL_RenderDrawPoint(this->_renderer, x + py, y - px);
        SDL_RenderDrawPoint(this->_renderer, x - py, y - px);
        SDL_RenderDrawPoint(this->_renderer, x - py, y + px);
        if (pk >= 0)
            py--;
        px++;
        pk = pk + (2 * (oldPx + 1)) + (pow(py, 2) - pow(oldPy, 2)) - (py - oldPy) + 1;
        oldPx = px;
        oldPy = py;
    }
}

void Arcade::Display::SDL::putFillCircle(float x, float y, float radius) const
{
    int pk = 1 - radius;
    int px = 0;
    int py = radius;
    int oldPx = 0;
    int oldPy = radius;

    this->putCircle(x, y, radius);
    x += radius;
    y += radius;
    while (py > px) {
        SDL_RenderDrawLine(this->_renderer, x - px, y - py, x + px, y - py);
        SDL_RenderDrawLine(this->_renderer, x - px, y - py, x + px, y - py);
        SDL_RenderDrawLine(this->_renderer, x - py, y + px, x + py, y + px);
        SDL_RenderDrawLine(this->_renderer, x - py, y - px, x + py, y - px);
        SDL_RenderDrawLine(this->_renderer, x - px, y + py, x + px, y + py);
        if (pk >= 0)
            py--;
        px++;
        pk = pk + (2 * (oldPx + 1)) + (pow(py, 2) - pow(oldPy, 2)) - (py - oldPy) + 1;
        oldPx = px;
        oldPy = py;
    }
}

void Arcade::Display::SDL::putText(const std::string &text, unsigned int size, float x, float y) const
{
    TTF_Font *font = TTF_OpenFont("./assets/pixelmix_bold.ttf", size);
    SDL_Surface *textSurface;
    SDL_Rect textRect;
    SDL_Texture *texture;

    if (font == NULL)
        throw Arcade::Exceptions::BadFileException("Cannot load font", "SDL::putText");
    textSurface = TTF_RenderText_Solid(font, text.c_str(), this->_libColors.at(this->_currentColor));
    if (textSurface == NULL)
        throw Arcade::Exceptions::BadInstanciationException("text surface creation failed.", "SDL::putText");
    texture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    textRect.x = (int)x;
    textRect.y = (int)y;
    textRect.h = 0;
    textRect.w = 0;
    SDL_FreeSurface(textSurface);
    SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(this->_renderer, texture, NULL, &textRect);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
}

const std::string &Arcade::Display::SDL::getLibName() const
{
    return this->_libName;
}