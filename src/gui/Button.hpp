/**
* @file Button.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of Button class.
*/

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <string>

#include <SDL/SDL_ttf.h>

typedef struct{
  int x, y;
  int w, h;
}TextBoundingBox_t;

class Button{
  public:
    /** Create buttown with text <c>text</c> using font <c>font</c>.
    * @param font Font to use.
    * @param text Text to write in button.
    */
    Button(TTF_Font* font, const std::string& text);

    /** Destructor. */
    ~Button();

    /** Draw the button.
    * @param screen Buffer to draw the buffer to.
    * @param position Position where to draw the button.
    * @param over Determine if draw the button as overed buton or no.
    */
    void draw(SDL_Surface* screen, SDL_Rect& position, bool over = false);

    /** @return bounding box. */
    TextBoundingBox_t getBoundingBox() const;

  private:
    SDL_Surface* _textNormal; /**< Pre rendered normal text. */
    SDL_Surface* _textOver; /**< Pre rendered over text. */
    TextBoundingBox_t _boundingBox; /**< Bounding box. */
};

/** Check if coordiantes inside bounding box.
* @param x X-Coordinate.
* @param y Y-Coordinate.
* @param box Bounding box.
* @return true if coordiantes inside bbox otherwise false.
*/
bool insideBoundingBox(const int x, const int y, const TextBoundingBox_t& box);

#endif // BUTTON_HPP_INCLUDED
