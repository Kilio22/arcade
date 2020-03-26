/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "games/Pacman.hpp"
#include "Exceptions/BadFileException.hpp"

const std::string Arcade::Games::Pacman::_mapPath = "./src/games/Pacman/maze.txt";

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Pacman>();
}

Arcade::Games::Pacman::Pacman()
    : AGameModule("Pacman")
{
    this->reset();
}

Arcade::Games::Pacman::Pacman::~Pacman()
{
}

void Arcade::Games::Pacman::reset()
{
    this->_currentScore = 0;
    this->_framesToStep = 8;
    this->_framesCount = 0;
    this->_bonuses.clear();
    this->_canEatMonsters = false;
    this->_direction = UP;
    this->_monsters.clear();
    this->_path.clear();
    this->_tokens.clear();
    this->_walls.clear();
    this->initMaze();
    this->initEntities();
}

void Arcade::Games::Pacman::update(const Arcade::Display::IDisplayModule &displayModule)
{
    this->_framesCount += displayModule.getDelta();
    this->updateDirection(displayModule);
    if (this->_canEatMonsters == true && (clock() - this->_eatClock) / CLOCKS_PER_SEC >= 8) {
        this->_canEatMonsters = false;
    }
    if (this->_framesCount >= this->_framesToStep) {
        this->moveMonsters();
        this->move();
        this->eat();
        if (this->isDead()) {
            this->addToBestScores(this->_currentScore);
            this->reset();
        }
        this->_framesCount = 0;
    }
}

void Arcade::Games::Pacman::updateDirection(const Arcade::Display::IDisplayModule &displayModule)
{
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::Z)) {
        this->_direction = Direction::UP;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::S)) {
        this->_direction = Direction::DOWN;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::D)) {
        this->_direction = Direction::RIGHT;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::Q)) {
        this->_direction = Direction::LEFT;
    }
}

void Arcade::Games::Pacman::moveMonsters(void)
{
    for (auto it = this->_monsters.begin(); it != this->_monsters.end(); it++) {
        Direction randDirection = static_cast<Direction>(std::rand() % 4);
        if (randDirection == Direction::UP && canMove(it->x, it->y - 15)) {
            it->y -= 15;
        }
        if (randDirection == Direction::DOWN && canMove(it->x, it->y + 15)) {
            it->y += 15;
        }
        if (randDirection == Direction::RIGHT && canMove(it->x + 15, it->y)) {
            it->x += 15;
        }
        if (randDirection == Direction::LEFT && canMove(it->x - 15, it->y)) {
            it->x -= 15;
        }
    }
}

void Arcade::Games::Pacman::move(void)
{
    if (this->_direction == Direction::UP && canMove(this->_pacman.x, this->_pacman.y - 15)) {
        this->_pacman.y -= 15;
    }
    if (this->_direction == Direction::DOWN && canMove(this->_pacman.x, this->_pacman.y + 15)) {
        this->_pacman.y += 15;
    }
    if (this->_direction == Direction::RIGHT && canMove(this->_pacman.x + 15, this->_pacman.y)) {
        this->_pacman.x += 15;
    }
    if (this->_direction == Direction::LEFT && canMove(this->_pacman.x - 15, this->_pacman.y)) {
        this->_pacman.x -= 15;
    }
}

bool Arcade::Games::Pacman::canMove(float x, float y)
{
    auto result = std::find_if(this->_walls.begin(), this->_walls.end(), [x, y](rectangle_t rect){
        if (x >= rect.x && x <= (rect.x + 15) && y >= rect.y && y <= (rect.y + 15))
            return true;
        return false;
    });
    return result == this->_walls.end();
}

bool Arcade::Games::Pacman::isDead(void)
{
    auto result = std::find_if(this->_monsters.begin(), this->_monsters.end(), [this](circle_t monster){
        if (this->_pacman.x >= monster.x && this->_pacman.x <= (monster.x + 8) && this->_pacman.y >= monster.y && this->_pacman.y <= (monster.y + 8) && this->_canEatMonsters == false)
            return true;
        return false;
    });
    return !(result == this->_monsters.end());
}

void Arcade::Games::Pacman::eat(void)
{
    this->_tokens.erase(std::remove_if(this->_tokens.begin(), this->_tokens.end(), [this](std::pair<rectangle_t, circle_t> token) {
        if (this->_pacman.x >= token.first.x && this->_pacman.x <= (token.first.x + 15) && this->_pacman.y >= token.first.y && this->_pacman.y <= (token.first.y + 15)) {
            this->_currentScore++;
            this->_path.push_back(token.first);
            return true;
        }
        return false;
    }), this->_tokens.end());
    this->_bonuses.erase(std::remove_if(this->_bonuses.begin(), this->_bonuses.end(), [this](std::pair<rectangle_t, rectangle_t> bonus) {
        if (this->_pacman.x >= bonus.first.x && this->_pacman.x <= (bonus.first.x + 15) && this->_pacman.y >= bonus.first.y && this->_pacman.y <= (bonus.first.y + 15)) {
            this->_currentScore += 10;
            this->_path.push_back(bonus.first);
            this->_eatClock = clock();
            this->_canEatMonsters = true;
            return true;
        }
        return false;
    }), this->_bonuses.end());
    this->_monsters.erase(std::remove_if(this->_monsters.begin(), this->_monsters.end(), [this](circle_t monster) {
        if (this->_pacman.x >= monster.x && this->_pacman.x <= (monster.x + 8) && this->_pacman.y >= monster.y && this->_pacman.y <= (monster.y + 8) && this->_canEatMonsters == true) {
            return true;
        }
        return false;
    }), this->_monsters.end());
    if (this->_monsters.size() != 4) {
        for (size_t i = this->_monsters.size(); i < 4; i++) {
            if (std::rand() % 2 == 0) {
                this->_monsters.push_back({292, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_BLUE});
            } else {
                this->_monsters.push_back({322, 234, 4, Arcade::Display::IDisplayModule::Colors::WHITE});
            }
        }
    }
}

void Arcade::Games::Pacman::render(Arcade::Display::IDisplayModule &displayModule) const
{
    this->drawMaze(displayModule);
    this->drawMonsters(displayModule);
    displayModule.setColor(this->_pacman.color);
    displayModule.putFillCircle(this->_pacman.x, this->_pacman.y, this->_pacman.radius);
}

void Arcade::Games::Pacman::drawMaze(Arcade::Display::IDisplayModule &displayModule) const
{
    for (auto bloc = this->_walls.begin(); bloc < this->_walls.end(); bloc++) {
        displayModule.setColor(bloc->color);
        displayModule.putFillRect(bloc->x, bloc->y, bloc->w, bloc->h);
    }
    for (auto bloc = this->_path.begin(); bloc < this->_path.end(); bloc++) {
        displayModule.setColor(bloc->color);
        displayModule.putFillRect(bloc->x, bloc->y, bloc->w, bloc->h);
    }
    for (auto token = this->_tokens.begin(); token < this->_tokens.end(); token++) {
        displayModule.setColor(token->second.color);
        displayModule.putFillCircle(token->second.x, token->second.y, token->second.radius);
    }
    for (auto bonus = this->_bonuses.begin(); bonus < this->_bonuses.end(); bonus++) {
        displayModule.setColor(bonus->second.color);
        displayModule.putFillRect(bonus->second.x, bonus->second.y, bonus->second.w, bonus->second.h);
    }
}

void Arcade::Games::Pacman::drawMonsters(Arcade::Display::IDisplayModule &displayModule) const
{
    for (auto monster = this->_monsters.begin(); monster < this->_monsters.end(); monster++) {
        displayModule.setColor(monster->color);
        displayModule.putFillCircle(monster->x, monster->y, monster->radius);
    }
}

void Arcade::Games::Pacman::initMaze(void)
{
    std::ifstream ifs(this->_mapPath);
    std::string line;
    float x = 0;
    float y = 7;
    bool hasWall = false;

    if (ifs.is_open() == false)
        throw Arcade::Exceptions::BadFileException("Cannot load pacman map.", "Pacman::Pacman");
    std::getline(ifs, line);
    int lineSize = line.size();
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    x = (WIDTH - lineSize * 15) / 2;
    while (std::getline(ifs, line)) {
        for (auto character = line.begin(); character < line.end(); character++) {
            if (*character == ' ' && hasWall == true) {
                this->_path.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::Colors::BLACK});
                this->_tokens.push_back({{x, y, 15, 15, Arcade::Display::IDisplayModule::Colors::BLACK}, {x + 4, y + 6, 1, Arcade::Display::IDisplayModule::Colors::YELLOW}});
            } else if (*character == '#') {
                hasWall = true;
                this->_walls.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::Colors::RED});
            }
            if (*character == 'O') {
                this->_path.push_back({x, y, 15, 15, Arcade::Display::IDisplayModule::Colors::BLACK});
                this->_bonuses.push_back({{x, y, 15, 15, Arcade::Display::IDisplayModule::Colors::BLACK}, {x + 3, y + 3, 8, 8, Arcade::Display::IDisplayModule::Colors::LIGHT_YELLOW}});
            }
            x += 15;
        }
        hasWall = false;
        x = (WIDTH - lineSize * 15) / 2;
        y += 15;
    }
    ifs.close();
}

void Arcade::Games::Pacman::initEntities(void)
{
    this->_monsters.push_back({292, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_BLUE});
    this->_monsters.push_back({307, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_CYAN});
    this->_monsters.push_back({322, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_GREEN});
    this->_monsters.push_back({337, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_GRAY});
    this->_pacman = {322, 355, 4, Arcade::Display::IDisplayModule::Colors::YELLOW};
}