/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#include "lib/SFML.hpp"
#include "Exceptions/BadFileException.hpp"

const std::string Arcade::Display::SFML::_libName = "SFML";
const std::vector<sf::Color> Arcade::Display::SFML::_libColors = {
    sf::Color::Black,
    sf::Color::Black,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Blue,
    sf::Color::Magenta,
    sf::Color::Cyan,
    sf::Color(128, 128, 128),
    sf::Color(105, 105, 105),
    sf::Color(240, 128, 128),
    sf::Color(0, 255, 111),
    sf::Color(255, 255, 64),
    sf::Color(0, 162, 255),
    sf::Color(255, 0, 247),
    sf::Color(0, 247, 255),
    sf::Color::White
};

const std::vector<sf::Keyboard::Key> Arcade::Display::SFML::_libKeys = {
    sf::Keyboard::Left,
    sf::Keyboard::Right,
    sf::Keyboard::Up,
    sf::Keyboard::Down,
    sf::Keyboard::Z,
    sf::Keyboard::Q,
    sf::Keyboard::S,
    sf::Keyboard::D,
    sf::Keyboard::A,
    sf::Keyboard::E,
    sf::Keyboard::W,
    sf::Keyboard::X,
    sf::Keyboard::Space,
    sf::Keyboard::Escape,
    sf::Keyboard::J,
    sf::Keyboard::K,
    sf::Keyboard::U,
    sf::Keyboard::I,
    sf::Keyboard::M,
    sf::Keyboard::R,
    sf::Keyboard::Enter
};

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SFML>();
}

Arcade::Display::SFML::SFML()
    : _window(nullptr), _currentColor(Colors::DEFAULT), _events(Keys::KEYS_END, false), _keyCode('\0')
{
}

Arcade::Display::SFML::~SFML()
{
    if (this->_window != nullptr) {
        this->_window->close();
        this->_window.release();
    }
}

void Arcade::Display::SFML::reset()
{
    this->clear();
}

void Arcade::Display::SFML::open()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(FULL_WIDTH, FULL_HEIGHT), "Arcade");
}

bool Arcade::Display::SFML::isOpen() const
{
    return this->_window->isOpen();
}

bool Arcade::Display::SFML::switchToNextLib() const
{
    return this->_events.at(Keys::RIGHT);
}

bool Arcade::Display::SFML::switchToPreviousLib() const
{
    return this->_events.at(Keys::LEFT);
}

bool Arcade::Display::SFML::switchToNextGame() const
{
    return this->_events.at(Keys::UP);
}

bool Arcade::Display::SFML::switchToPreviousGame() const
{
    return this->_events.at(Keys::DOWN);
}

bool Arcade::Display::SFML::shouldBeRestarted() const
{
    return this->_events.at(Keys::R);
}

bool Arcade::Display::SFML::shouldGoToMenu() const
{
    return this->_events.at(Keys::M);
}

bool Arcade::Display::SFML::shouldExit() const
{
    return this->_events.at(Keys::ESCAPE);
}

bool Arcade::Display::SFML::isKeyPressed(Keys key) const
{
    return sf::Keyboard::isKeyPressed(this->_libKeys.at(key));
}

bool Arcade::Display::SFML::isKeyPressedOnce(Keys key) const
{
    return this->_events.at(key);
}

float Arcade::Display::SFML::getDelta() const
{
    return 1;
}

void Arcade::Display::SFML::clear() const
{
    this->_window->clear(sf::Color::Black);
}

void Arcade::Display::SFML::update()
{
    sf::Event event;

    this->_events.assign(Keys::KEYS_END, false);
    this->_keyCode = '\0';
    while (this->_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            auto found = std::find(this->_libKeys.begin(),this->_libKeys.end(), event.key.code);
            if (found != this->_libKeys.end())
                this->_events[std::distance(this->_libKeys.begin(), found)] = true;
        }
        if (event.type == sf::Event::TextEntered) {
            this->_keyCode = event.text.unicode;
        }
    }
}

void Arcade::Display::SFML::render() const
{
    this->_window->display();
}

char Arcade::Display::SFML::getKeyCode() const
{
    if (this->_keyCode == '\b')
        return this->_keyCode;
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

void Arcade::Display::SFML::setColor(Colors color)
{
    this->_currentColor = color;
}

void Arcade::Display::SFML::putPixel(float x, float y) const
{
    this->putFillRect(x, y, 1, 1);
}

void Arcade::Display::SFML::putLine(float x1, float y1, float x2, float y2) const
{
    if (x1 < 0) {
        x1 *= -1;
        x2 *= -1;
        y1 *= -1;
        y2 *= -1;
    } else if (x1 >= 0) {
        x1 += (FULL_WIDTH - WIDTH) / 2;
        x2 += (FULL_WIDTH - WIDTH) / 2;
        y1 += (FULL_HEIGHT - HEIGHT) / 2;
        y2 += (FULL_HEIGHT - HEIGHT) / 2;
    }
    sf::Vertex p1(sf::Vector2f(x1, y1), this->_libColors.at(this->_currentColor));
    sf::Vertex p2(sf::Vector2f(x2, y2), this->_libColors.at(this->_currentColor));
    sf::Vertex vertices[2] = {
        p1,
        p2
    };

    this->_window->draw(vertices, 2, sf::Lines);
}

void Arcade::Display::SFML::putRect(float x, float y, float w, float h) const
{
    sf::RectangleShape rect;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(3);
    rect.setOutlineColor(this->_libColors.at(this->_currentColor));
    rect.setFillColor(this->_libColors[DEFAULT]);
    this->_window->draw(rect);
}

void Arcade::Display::SFML::putFillRect(float x, float y, float w, float h) const
{
    sf::RectangleShape rect;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setOutlineColor(this->_libColors.at(this->_currentColor));
    rect.setFillColor(this->_libColors.at(this->_currentColor));
    this->_window->draw(rect);
}

void Arcade::Display::SFML::putCircle(float x, float y, float rad) const
{
    sf::CircleShape circle;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    circle.setPosition(sf::Vector2f(x, y));
    circle.setRadius(rad);
    circle.setOutlineColor(this->_libColors.at(this->_currentColor));
    this->_window->draw(circle);
}

void Arcade::Display::SFML::putFillCircle(float x, float y, float rad) const
{
    sf::CircleShape circle;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    circle.setPosition(sf::Vector2f(x, y));
    circle.setRadius(rad);
    circle.setOutlineColor(this->_libColors.at(this->_currentColor));
    circle.setFillColor(this->_libColors.at(this->_currentColor));
    this->_window->draw(circle);
}

void Arcade::Display::SFML::putText(const std::string &text, unsigned int size, float x, float y) const
{
    sf::Text newText;
    sf::Font newFont;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    if (newFont.loadFromFile("./assets/pixelmix_bold.ttf") == false)
        throw Arcade::Exceptions::BadFileException("Cannot load font", "SFML::putText");
    newText.setFont(newFont);
    newText.setFillColor(this->_libColors.at(this->_currentColor));
    newText.setCharacterSize(size);
    newText.setString(text);
    newText.setPosition(sf::Vector2f(x, y));
    this->_window->draw(newText);
}

const std::string &Arcade::Display::SFML::getLibName() const
{
    return this->_libName;
}
