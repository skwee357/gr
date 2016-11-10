/**
* @file MainMenu.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of MainMenu class.
*/

#include <SDL/SDL_draw.h>

#include "MainMenu.hpp"

MainMenu::MainMenu(TTF_Font* font)
{
  _cube = _pyramid = _exit = 0;
  #ifdef _DEBUG
  _debug = 0;
  #endif
  _overed = 0;

  if(font == 0)
    return;

  _cube = new Button(font, "Cube");
  _pyramid = new Button(font, "Pyramid");
  _exit = new Button(font, "Exit");

  #ifdef _DEBUG
  _debug = new Button(font, "Debug Info");
  #endif
}

MainMenu::~MainMenu()
{
  if(_cube)
    delete _cube;

  if(_pyramid)
    delete _pyramid;

  if(_exit)
    delete _exit;

  #ifdef _DEBUG
  if(_debug)
    delete _debug;
  #endif
}

void MainMenu::handleInput(SDL_Event& event, int& buttonPressed)
{
  TextBoundingBox_t b1, b2, b3;
  int mx, my;

  b1 = _cube->getBoundingBox();
  b2 = _pyramid->getBoundingBox();
  b3 = _exit->getBoundingBox();

  #ifdef _DEBUG
  TextBoundingBox_t b4;
  b4 = _debug->getBoundingBox();
  #endif

  SDL_GetMouseState(&mx, &my);

  _overed = 0;

  if(insideBoundingBox(mx, my, b1) == true)
    _overed = 1;

  if(insideBoundingBox(mx, my, b2) == true)
    _overed = 2;

  if(insideBoundingBox(mx, my, b3) == true)
    _overed = 3;

  #ifdef _DEBUG
  if(insideBoundingBox(mx, my, b4) == true)
    _overed = 4;
  #endif

  if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
    buttonPressed = _overed;
}

void MainMenu::draw(SDL_Surface* screen)
{
  SDL_Rect p1, p2, p3;
  p1.x = p2.x = p3.x = 360;
  p1.y = 290;
  p2.y = 340;
  p3.y = 390;

  #ifdef _DEBUG
  SDL_Rect p4;
  p4.x = 40;
  p4.y = 40;
  #endif

  _cube->draw(screen, p1, (_overed == 1) ? true : false);
  _pyramid->draw(screen, p2, (_overed == 2) ? true : false);
  _exit->draw(screen, p3, (_overed == 3) ? true : false);
  #ifdef _DEBUG
  _debug->draw(screen, p4, (_overed == 4) ? true : false);
  #endif

  TextBoundingBox_t b1, b2, b3;
  b1 = _cube->getBoundingBox();
  b2 = _pyramid->getBoundingBox();
  b3 = _exit->getBoundingBox();
  int maxw, maxh;
  int x, y;

  if((b1.w > b2.w) && (b1.w > b3.w))
    maxw = b1.w;
  else if((b2.w > b1.w) && (b2.w > b3.w))
    maxw = b2.w;
  else if((b3.w > b1.w) && (b3.w > b2.w))
    maxw = b3.w;
  else
    maxw = b1.w;

  if((b1.h > b2.h) && (b1.h > b3.h))
    maxh = b1.h;
  else if((b2.h > b1.h) && (b2.h > b3.h))
    maxh = b2.h;
  else if((b3.h > b1.h) && (b3.h > b2.h))
    maxh = b3.h;
  else
    maxh = b1.h;

  x = p1.x - 30;
  y = p1.y - 20;
  maxw += 40;
  maxh += 130;

  static Uint32 lineCl = SDL_MapRGB(screen->format, 20, 20, 20);
  Draw_HLine(screen, x,        y,        x + maxw, lineCl);
  Draw_HLine(screen, x,        y + maxh, x + maxw, lineCl);
  Draw_VLine(screen, x,        y,        y + maxh, lineCl);
  Draw_VLine(screen, x + maxw, y,        y + maxh, lineCl);
}
