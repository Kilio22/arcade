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

#define FULL_WIDTH 1792
#define FULL_HEIGHT 936
#define WIDTH 640
#define HEIGHT 480

/** \namespace Arcade::Display
 *  Contains elements related to the display libraries of the Arcade project.
 */
namespace Arcade::Display
{
    /**
     * @brief Interface for the display modules used to display things.
     */
    class IDisplayModule
    {
        public:
            virtual ~IDisplayModule() = default;

            /**
             * @brief Available colors.
             */
            enum Colors
            {
                DEFAULT, ///< The color the window clears to
                BLACK, ///< Black color
                RED, ///< Red color
                GREEN, ///< Green color
                YELLOW, ///< Yellow color
                BLUE, ///< Blue color
                MAGENTA, ///< Magenta color
                CYAN, ///< Cyan color
                LIGHT_GRAY, ///< Light gray color
                DARK_GRAY, ///< Dark gray color
                LIGHT_RED, ///< Light red color
                LIGHT_GREEN, ///< Light green color
                LIGHT_YELLOW, ///< Light yellow color
                LIGHT_BLUE, ///< Light blue color
                LIGHT_MAGENTA, ///< Light magenta color
                LIGHT_CYAN, ///< Light cyan color
                WHITE, ///< White color
                COLORS_END ///< Color count
            };

            /**
             * @brief Available keys
             */
            enum Keys
            {
                LEFT, ///< Left key
                RIGHT, ///< Right key
                UP, ///< Up key
                DOWN, ///< Down key
                Z, ///< Z key
                Q, ///< Q key
                S, ///< S key
                D, ///< D key
                A, ///< A key
                E, ///< E key
                W, ///< W key
                X, ///< X key
                SPACE, ///< Space key
                ESCAPE, ///< Backspace key
                J, ///< J key
                K, ///< K key
                U, ///< U key
                I, ///< I key
                M, ///< M key
                R, ///< R key
                ENTER, ///< Return key
                KEYS_END ///< Key count
            };


            /**
             * @brief Resets the library
             */
            virtual void reset() = 0;

            /**
             * @brief Opens / initializes the window.
             */
            virtual void open() = 0;

            /**
             * @brief Check window status
             * @return true Window is open
             * @return false Window is closed
             */
            virtual bool isOpen() const = 0;


            /**
             * @brief Checks whether you need to change the current display library.
             * @return true Switch to next available library
             * @return false Do nothing
             */
            virtual bool switchToNextLib() const = 0;

            /**
             * @brief Checks whether you need to change the current display library.
             * @return true Switch to previous available library
             * @return false Do nothing
             */
            virtual bool switchToPreviousLib() const = 0;

            /**
             * @brief Checks whether you need to change the current game library.
             * @return true Switch to next available library
             * @return false Do nothing
             */
            virtual bool switchToNextGame() const = 0;

            /**
             * @brief Checks whether you need to change the current game library.
             * @return true Switch to previous available library
             * @return false Do nothing
             */
            virtual bool switchToPreviousGame() const = 0;

            /**
             * @brief Checks whether you need to restart the current game.
             * @return true Restart the game
             * @return false Do nothing
             */
            virtual bool shouldBeRestarted() const = 0;

            /**
             * @brief Checks whether you need to go back to the menu.
             * @return true Go back to menu
             * @return false Do nothing
             */
            virtual bool shouldGoToMenu() const = 0;

            /**
             * @brief Checks whether you need to exit the program.
             * @return true Exit the program
             * @return false Do nothing
             */
            virtual bool shouldExit() const = 0;


            /**
             * @brief Checks whether the current key is being pressed.
             * @return true Key is pressed
             * @return false Key is not pressed
             */
            virtual bool isKeyPressed(IDisplayModule::Keys) const = 0;

            /**
             * @brief Checks whether the current key was pressed during the last frame.
             * @return true Key is pressed
             * @return false Key is not pressed
             */
            virtual bool isKeyPressedOnce(IDisplayModule::Keys) const = 0;


            /**
             * @brief Gets the number of frames since last update
             * @return float Frame count
             */
            virtual float getDelta() const = 0;


            /**
             * @brief Clears the canvas
             */
            virtual void clear() const = 0;

            /**
             * @brief Runs an update over the events that occured.
             */
            virtual void update() = 0;

            /**
             * @brief Renders the canvas
             */
            virtual void render() const = 0;


            /**
             * @brief Gets the last pressed character from the keyboard
             * @return \0 if nothing was pressed, \\b if backspace was pressed, \\n if return was pressed,
             * otherwise, a character.
             */
            virtual char getKeyCode() const = 0;


            /**
             * @brief Defines the color of the elements that will be drawn.
             * @param col The color
             */
            virtual void setColor(IDisplayModule::Colors col) = 0;

            /**
             * @brief Displays a pixel
             * @param x X coordinates
             * @param y Y coordinates
             */
            virtual void putPixel(float x, float y) const = 0;

            /**
             * @brief Displays a line
             * @param x1 X coordinates for the first point
             * @param y1 Y coordinates for the first point
             * @param x2 X coordinates for the second point
             * @param y2 Y coordinates for the second point
             */
            virtual void putLine(float x1, float y1, float x2, float y2) const = 0;

            /**
             * @brief Displays a rectangle
             * @param x X coordinates
             * @param y Y coordinates
             * @param w Width of the rectangle
             * @param h Height of the rectangle
             */
            virtual void putRect(float x, float y, float w, float h) const = 0;

            /**
             * @brief Displays a filled rectangle
             * @param x X coordinates
             * @param y Y coordinates
             * @param w Width of the rectangle
             * @param h Height of the rectangle
             */
            virtual void putFillRect(float x, float y, float w, float h) const = 0;

            /**
             * @brief Displays a cirle
             * @param x X coordinates
             * @param y Y coordinates
             * @param rad Radius of the circle
             */
            virtual void putCircle(float x, float y, float rad) const = 0;

            /**
             * @brief Displays a filled cirle
             * @param x X coordinates
             * @param y Y coordinates
             * @param rad Radius of the circle
             */
            virtual void putFillCircle(float x, float y, float rad) const = 0;

            /**
             * @brief Displays text
             * @param text The text content
             * @param size The text size
             * @param x X coordinates
             * @param y Y coordinates
             */
            virtual void putText(const std::string &text, unsigned int size, float x, float y) const = 0;

            /**
             * @brief Gets the library name
             * @return The library's name
             */
            virtual const std::string &getLibName() const = 0;
    };
} // namespace Arcade::Display

#endif /* !IDISPLAYMODULE_HPP_ */
