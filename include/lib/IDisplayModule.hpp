/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <iostream>
#include <vector>
#include <tuple>

#define SAVE_PATH "games/.saves/"
#define WIDTH 640
#define HEIGHT 480

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        // Limited to the bash color codes in case colors aren't handled by a library
        enum Colors {
            DEFAULT,
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            LIGHT_GRAY,
            DARK_GRAY,
            LIGHT_RED,
            LIGHT_GREEN,
            LIGHT_YELLOW,
            LIGHT_BLUE,
            LIGHT_MAGENTA,
            LIGHT_CYAN,
            WHITE,
            COLORS_END
        };

        // Keys you have to implement, there are enough keys to have multiple keyboard configurations for every game
        // You only need 6 keys for the core and 6 for the games.
        enum Keys {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            Z,
            Q,
            S,
            D,
            A,
            E,
            W,
            X,
            SPACE,
            ESCAPE,
            J,
            K,
            U,
            I,
            M,
            R,
            KEYS_END
        };

        // For the core
        // Reset the library
        virtual void reset() = 0;
        // Check if the window is open
        virtual bool isOpen() = 0;

        // Handle switching libs & games (the names are explicit)
        // Those are all key presses
        // Those must be different than the keys listed in the Keys enum.
        // The keys enum only lists keys used by games, not special keys to switch libraries.
        virtual bool switchToNext_lib() = 0;
        virtual bool switchToPrevious_lib() = 0;
        virtual bool switchToNext_game() = 0;
        virtual bool switchToPrevious_game() = 0;
        // From the pdf
        virtual bool shouldBeRestarted() = 0;
        virtual bool shouldGoToMenu() = 0;
        virtual bool shouldExit() = 0;

        // Handle Inputs & Events
        virtual bool isKeyPressed(IDisplayModule::Keys) = 0;
        virtual bool isKeyPressedOnce(IDisplayModule::Keys) = 0;
        // Get the number of frames that passed between two calls to this function
        // The games should not be frame dependant!! That's why this is here.
        virtual float getDelta() = 0;

        // Handle Loop
        virtual void clear() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        // You don't need all three of them, only one should be enough but we added the three of them
        // in case some of you want to seperate each step
        // Your core (or games) should nonetheless call all of these functions in this specific order :
        // clear -> update -> render

        // Handle Text Input
        // We need to ask for the player's name (check the pdf before complaining and asking about this function)
        virtual std::string getPlayerName() = 0;
        virtual void setPlayerName(std::string) = 0;

        // Display Stuff
        // Sets the color for all the following draw functions.
        // everything you display after this will have the selected color
        virtual void setColor(IDisplayModule::Colors col) = 0;
        // Display a pixel
        virtual void putPixel(float x, float y) = 0;
        // Display a line
        virtual void putLine(float x1, float y1, float x2, float y2) = 0;
        // Display an empty rectangle
        virtual void putRect(float x, float y, float w, float h) = 0;
        // Display a full rectangle
        virtual void putFillRect(float x, float y, float w, float h) = 0;
        // Display an empty circle
        virtual void putCircle(float x, float y, float rad) = 0;
        // Display a full circle
        virtual void putFillCircle(float x, float y, float rad) = 0;
        // Display some text
        virtual void putText(std::string text, float size, float x, float y) = 0;

        // We chose not to display images because some library can't and it would cause other problems
        // You can still parse a file and display pixel art images by displaying pixels manually if you want.

        // Strictly for debugging purposes, get the library's name (ncurses/sfm/sdl/libcaca etc etc)
        virtual std::string getLibName() const = 0;
};

#endif /* !IDISPLAYMODULE_HPP_ */
