/**
* @file MainMenu.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of MainMenu class.
*/

#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Button.hpp"

class MainMenu{
  public:
    /** Create new Buttons with text.
    * @param font Text to use.
    */
    MainMenu(TTF_Font* font);

    /** Destructor. */
    ~MainMenu();

    /** Hanlde menu input.
    * @param event Event queue.
    * @param buttonPressed Button pressed (0 if not pressed).
    */
    void handleInput(SDL_Event& event, int& buttonPressed);

    /** Draw menu.
    * @param screen Where to draw.
    */
    void draw(SDL_Surface* screen);

  private:
    Button* _cube; /**< Cube. */
    Button* _pyramid; /**< Pyramid. */
    Button* _exit; /**< Exit button. */
    #ifdef _DEBUG
    Button* _debug;
    #endif
    int _overed; /**< Overed button. */
};

#endif // MAINMENU_HPP_INCLUDED
