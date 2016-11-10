/**
* @file Button.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of Button class.
*/

#include <SDL/SDL_draw.h>

#include "Button.hpp"


bool insideBoundingBox(const int x, const int y, const TextBoundingBox_t& box)
{
  if((x >= box.x) && (x <= (box.x + box.w)) && (y >= box.y) && (y <= (box.y + box.h)))
    return true;
  return false;
}

Button::Button(TTF_Font* font, const std::string& text)
{
  _boundingBox.h = _boundingBox.w = _boundingBox.x = _boundingBox.y = 0;

  _textNormal = _textOver = 0;

  if(font == 0)
    return;

  SDL_Color normalCl = {255, 255, 255, 0};
  SDL_Color overCl = {255, 0, 0, 0};

  //Get width and height of bbox
  TTF_SizeText(font, text.c_str(), &_boundingBox.w, &_boundingBox.h);

  _boundingBox.w += 20;
  _boundingBox.h += 10;

  _textNormal = TTF_RenderText_Blended(font, text.c_str(), normalCl);
  _textOver = TTF_RenderText_Blended(font, text.c_str(), overCl);
}

Button::~Button()
{
  if(_textNormal != 0)
    SDL_FreeSurface(_textNormal);

  if(_textOver != 0)
    SDL_FreeSurface(_textOver);
}

void Button::draw(SDL_Surface* screen, SDL_Rect& position, bool over)
{
  _boundingBox.x = position.x - 10;
  _boundingBox.y = position.y - 5;

  if(over)
    SDL_BlitSurface(_textOver, NULL, screen, &position);
  else
    SDL_BlitSurface(_textNormal, NULL, screen, &position);

  /*static Uint32 normalLineCl = SDL_MapRGB(screen->format, 0, 0, 0);
  static Uint32 overLineCl = SDL_MapRGB(screen->format, 150, 150, 150);*/
  static Uint32 normalLineCl = SDL_MapRGB(screen->format, 100, 100, 100);
  static Uint32 overLineCl = SDL_MapRGB(screen->format, 100, 100, 100);

  //Draw lines

  /*if(over) {
      Draw_HLine(screen, _boundingBox.x, _boundingBox.y,
                 _boundingBox.x + _boundingBox.w, normalLineCl);
      Draw_VLine(screen, _boundingBox.x, _boundingBox.y,
                 _boundingBox.y + _boundingBox.h, normalLineCl);
      Draw_HLine(screen, _boundingBox.x, _boundingBox.y +_boundingBox.h,
                 _boundingBox.x + _boundingBox.w, overLineCl);
      Draw_VLine(screen, _boundingBox.x + _boundingBox.w, _boundingBox.y,
                 _boundingBox.y + _boundingBox.h, overLineCl);
  } else {*/
      Draw_HLine(screen, _boundingBox.x, _boundingBox.y,
                 _boundingBox.x + _boundingBox.w, overLineCl);
      Draw_VLine(screen, _boundingBox.x, _boundingBox.y,
                 _boundingBox.y + _boundingBox.h, overLineCl);
      Draw_HLine(screen, _boundingBox.x, _boundingBox.y +_boundingBox.h,
                 _boundingBox.x + _boundingBox.w, normalLineCl);
      Draw_VLine(screen, _boundingBox.x + _boundingBox.w, _boundingBox.y,
                 _boundingBox.y + _boundingBox.h, normalLineCl);
  //}

  /*
  Draw_Line(screen, _boundingBox.x, _boundingBox.y,
            _boundingBox.x + _boundingBox.w, _boundingBox.y,
            lineCl);
  Draw_Line(screen, _boundingBox.x, _boundingBox.y + _boundingBox.h,
            _boundingBox.x + _boundingBox.w, _boundingBox.y + _boundingBox.h,
            lineCl);
  Draw_Line(screen, _boundingBox.x, _boundingBox.y,
            _boundingBox.x, _boundingBox.y + _boundingBox.h,
            lineCl);
  Draw_Line(screen, _boundingBox.x + _boundingBox.w, _boundingBox.y,
            _boundingBox.x + _boundingBox.w, _boundingBox.y + _boundingBox.h,
            lineCl);*/
}

TextBoundingBox_t Button::getBoundingBox() const
{
  return _boundingBox;
}
