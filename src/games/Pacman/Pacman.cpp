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
    this->_isDead = false;
    this->_framesCount = 0;
    this->_bonuses.clear();
    this->_canEatMonsters = false;
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
    if (this->_isDead == false) {
        this->updateDirection(displayModule);
        if (this->_canEatMonsters == true && (clock() - this->_eatClock) / CLOCKS_PER_SEC >= 8) {
            this->_canEatMonsters = false;
        }
        if (this->_framesCount >= this->_framesToStep) {
            this->moveMonsters();
            this->moveEntity(this->_pacman);
            this->eat();
            if (this->isDead()) {
                this->addToBestScores(this->_currentScore);
            }
            this->_framesCount = 0;
        }
    }
}

void Arcade::Games::Pacman::updateDirection(const Arcade::Display::IDisplayModule &displayModule)
{
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::Z)) {
        this->_pacman.second = Direction::UP;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::S)) {
        this->_pacman.second = Direction::DOWN;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::D)) {
        this->_pacman.second = Direction::RIGHT;
    }
    if (displayModule.isKeyPressedOnce(Arcade::Display::IDisplayModule::Keys::Q)) {
        this->_pacman.second = Direction::LEFT;
    }
}

void Arcade::Games::Pacman::moveMonsters(void)
{
    for (auto it = this->_monsters.begin(); it != this->_monsters.end(); it++) {
        if (this->moveEntity(*it) == false) {
            this->moveRandomDirection(*it);
        }
    }
}

void Arcade::Games::Pacman::moveRandomDirection(std::pair<circle_t, Direction> &entity)
{
    while (1) {
        Direction randDirection = static_cast<Direction>(std::rand() % 4);
        if (randDirection == Direction::UP && randDirection != entity.second && canMove(entity.first.x, entity.first.y - 15)) {
            entity.first.y -= 15;
            entity.second = randDirection;
            break;
        }
        if (randDirection == Direction::DOWN && randDirection != entity.second && canMove(entity.first.x, entity.first.y + 15)) {
            entity.first.y += 15;
            entity.second = randDirection;
            break;
        }
        if (randDirection == Direction::RIGHT && randDirection != entity.second && canMove(entity.first.x + 15, entity.first.y)) {
            entity.first.x += 15;
            entity.second = randDirection;
            break;
        }
        if (randDirection == Direction::LEFT && randDirection != entity.second && canMove(entity.first.x - 15, entity.first.y)) {
            entity.first.x -= 15;
            entity.second = randDirection;
            break;
        }
    }
}

bool Arcade::Games::Pacman::moveEntity(std::pair<circle_t, Direction> &entity)
{
    if (entity.second == Direction::UP && canMove(entity.first.x, entity.first.y - 15)) {
        entity.first.y -= 15;
        return true;
    }
    if (entity.second == Direction::DOWN && canMove(entity.first.x, entity.first.y + 15)) {
        entity.first.y += 15;
        return true;
    }
    if (entity.second == Direction::RIGHT && canMove(entity.first.x + 15, entity.first.y)) {
        entity.first.x += 15;
        return true;
    }
    if (entity.second == Direction::LEFT && canMove(entity.first.x - 15, entity.first.y)) {
        entity.first.x -= 15;
        return true;
    }
    return false;
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
    auto result = std::find_if(this->_monsters.begin(), this->_monsters.end(), [this](std::pair<circle_t, Direction> const &monster){
        if (this->_pacman.first.x >= monster.first.x && this->_pacman.first.x <= (monster.first.x + 8) && this->_pacman.first.y >= monster.first.y && this->_pacman.first.y <= (monster.first.y + 8) && this->_canEatMonsters == false)
            return true;
        return false;
    });
    this->_isDead = !(result == this->_monsters.end());
    return this->_isDead;
}

void Arcade::Games::Pacman::eat(void)
{
    this->_tokens.erase(std::remove_if(this->_tokens.begin(), this->_tokens.end(), [this](std::pair<rectangle_t, circle_t> token) {
        if (this->_pacman.first.x >= token.first.x && this->_pacman.first.x <= (token.first.x + 15) && this->_pacman.first.y >= token.first.y && this->_pacman.first.y <= (token.first.y + 15)) {
            this->_currentScore++;
            return true;
        }
        return false;
    }), this->_tokens.end());
    this->_bonuses.erase(std::remove_if(this->_bonuses.begin(), this->_bonuses.end(), [this](std::pair<rectangle_t, rectangle_t> bonus) {
        if (this->_pacman.first.x >= bonus.first.x && this->_pacman.first.x <= (bonus.first.x + 15) && this->_pacman.first.y >= bonus.first.y && this->_pacman.first.y <= (bonus.first.y + 15)) {
            this->_currentScore += 10;
            this->_eatClock = clock();
            this->_canEatMonsters = true;
            return true;
        }
        return false;
    }), this->_bonuses.end());
    this->_monsters.erase(std::remove_if(this->_monsters.begin(), this->_monsters.end(), [this](std::pair<circle_t, Direction> monster) {
        if (this->_pacman.first.x >= monster.first.x && this->_pacman.first.x <= (monster.first.x + 8) && this->_pacman.first.y >= monster.first.y && this->_pacman.first.y <= (monster.first.y + 8) && this->_canEatMonsters == true) {
            return true;
        }
        return false;
    }), this->_monsters.end());
    if (this->_monsters.size() != 4) {
        for (size_t i = this->_monsters.size(); i < 4; i++) {
            if (std::rand() % 2 == 0) {
                this->_monsters.push_back({{307, 220, 4, static_cast<Arcade::Display::IDisplayModule::Colors>(std::rand() % Arcade::Display::IDisplayModule::Colors::COLORS_END)}, Direction::UP});
            } else {
                this->_monsters.push_back({{322, 220, 4, static_cast<Arcade::Display::IDisplayModule::Colors>(std::rand() % Arcade::Display::IDisplayModule::Colors::COLORS_END)}, Direction::UP});
            }
        }
    }
}

void Arcade::Games::Pacman::render(Arcade::Display::IDisplayModule &displayModule) const
{
    this->drawMaze(displayModule);
    this->drawMonsters(displayModule);
    displayModule.setColor(this->_pacman.first.color);
    displayModule.putFillCircle(this->_pacman.first.x, this->_pacman.first.y, this->_pacman.first.radius);
    if (this->_isDead == true)
        this->displayGameOver(displayModule);
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
        displayModule.setColor(monster->first.color);
        displayModule.putFillCircle(monster->first.x, monster->first.y, monster->first.radius);
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
    this->_monsters.push_back({{307, 220, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_BLUE}, Direction::UP});
    this->_monsters.push_back({{322, 220, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_CYAN}, Direction::UP});
    this->_monsters.push_back({{307, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_GREEN}, Direction::UP});
    this->_monsters.push_back({{322, 234, 4, Arcade::Display::IDisplayModule::Colors::LIGHT_GRAY}, Direction::UP});
    this->_pacman = {{322, 355, 4, Arcade::Display::IDisplayModule::Colors::YELLOW}, Direction::UP};
}