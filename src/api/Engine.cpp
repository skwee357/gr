/**
* @file Engine.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of engine class.
*/

#include <iostream>
#include <cmath>
#include <string>

#include <SDL/SDL_image.h>
#include <SDL/SDL_draw.h>

#include "Engine.hpp"
#include "../utils/Exception.hpp"
#include "../math/Math.hpp"


Engine::Engine(int width, int height, int bpp, bool fullscreen)
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    throw Exception("Cannot initialize SDL");

  Uint32 flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
  if(fullscreen)
    flags |= SDL_FULLSCREEN;

  if((_screen = SDL_SetVideoMode(width, height, bpp, flags)) == 0)
    throw Exception("Cannot set video mode");

  _window.width = width;
  _window.height = height;
  _window.bpp = bpp;
  _window.fullscreen = fullscreen;

  _currentColor.r = _currentColor.g = _currentColor.b =_currentColor.a = 1.0f;
  _clearColor = SDL_MapRGB(_screen->format, 128, 128, 128);
  _vertexList.clear();

  _perspectiveRatio = 2500.0f;

  SDL_WM_SetCaption("3D fractals!", 0);
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  _engineState = MAIN_MENU_STATE;

  if(TTF_Init() == -1) {
    std::cout << "Cannot init ttf" << std::endl;
    _font = 0;
  } else {
    _font = TTF_OpenFont("res/Vera.ttf", 14);
    if(_font == 0)
      std::cout << "Cannot load Vera.ttf font" << std::endl;
  }

  _menu = new MainMenu(_font);

  _isRunning = true;

  _menuBg = 0;

  _menuBg = IMG_Load("res/menu.gif");

  if(_menuBg == 0)
    std::cout << "Cannot load menu background." << std::endl;

  _lastTime = SDL_GetTicks();

  _renderMode = RENDER_LINES;
  _triangleMode = TRIANGLE_NORMAL;

  _zbuffer = new ZBuffer_t*[_window.width];

  for(int i = 0; i < _window.width; i++)
    _zbuffer[i] = new ZBuffer_t[_window.height];

  #ifdef _DEBUG
  SDL_Color cl = {255, 0, 0, 0};
  _pfRegistred = 0;
  _pfRegistred = TTF_RenderText_Blended(_font, "Debug Info Saved to stdout.txt", cl);
  #endif

  SDL_Color credit = {255, 255, 255, 0};
  _credit = 0;
  _credit = TTF_RenderText_Blended(_font, "All right reserved to Dmitri Koudriavtsev, Yud-bet1 Shevah Mofet", credit);

  _vertices = 0;

  _lightCoficient = 0.89f;
  _enableLight = false;
}

Engine::~Engine()
{
  if(_menuBg)
    SDL_FreeSurface(_menuBg);

  if(_menu)
    delete _menu;

  #ifdef _DEBUG
  if(_pfRegistred)
    SDL_FreeSurface(_pfRegistred);
  #endif

  if(_credit)
    SDL_FreeSurface(_credit);

  if(_font != 0)
    TTF_CloseFont(_font);

  if(TTF_WasInit())
    TTF_Quit();

  for(int i = 0; i < _window.width; i++)
    delete []_zbuffer[i];
  delete []_zbuffer;

  if(SDL_WasInit(SDL_INIT_VIDEO))
    SDL_Quit();
}

void Engine::loadIdentity()
{
  _modelviewMatrix.identity();
  _modelviewMatrix.createTranslation(static_cast<float>(_window.width / 2),
                                     static_cast<float>(_window.height / 2),
                                     0.0f);
}

void Engine::translate(float dx, float dy, float dz)
{
  Matrix temp;
  temp.createTranslation(dx, dy, dz);

  _modelviewMatrix = _modelviewMatrix * temp;
}

void Engine::rotate(float angle, int x, int y, int z)
{
  Matrix temp;
  if(x)
    temp.createRotationX(angle);
  else if(y)
    temp.createRotationY(angle);
  else if(z)
    temp.createRotationZ(angle);

  _modelviewMatrix = _modelviewMatrix * temp;
}

void Engine::clearScreen()
{
  if(_engineState == MAIN_MENU_STATE) {
    //SDL_FillRect(_screen, NULL, _clearColor);
    SDL_Rect pos;
    pos.x = 10;
    pos.y = 580;
    SDL_BlitSurface(_menuBg, NULL, _screen, NULL);
    SDL_BlitSurface(_credit, NULL, _screen, &pos);
  } /*else if(_engineState == GAME_STATE){
    //if(_renderMode == RENDER_LINES)
      //SDL_FillRect(_screen, NULL, _clearColor);
  }*/

  _currentColor.r = _currentColor.g = _currentColor.b =_currentColor.a = 1.0f;
}

void Engine::clearZbuffer()
{
  #ifdef _DEBUG
  _pfManager.getInstance().start("ZBuffer cleaning");
  #endif
  for(int i = 0; i < _window.width; i++) {
    for(int j = 0; j < _window.height; j++) {
      _zbuffer[i][j].z = 0;
      _zbuffer[i][j].color = _clearColor;
    }
  }
  #ifdef _DEBUG
  _pfManager.getInstance().stop("ZBuffer cleaning");
  #endif
}

void Engine::updateScreen()
{
  if(_engineState == MAIN_MENU_STATE) {
    _menu->draw(_screen);
    _vertexList.clear();
  } else if(_engineState == GAME_STATE) {
    processDrawing();
  }

  //Update FPS
  static int frames = 0;
  static int fps = 0;
  frames++;

  if(((SDL_GetTicks() - _lastTime) * 0.001f) >= 1.0f) {
    fps = frames;
    frames = 0;
    _lastTime = SDL_GetTicks();
  }
  char f[64];
  #ifdef _DEBUG
  sprintf(f, "DEBUG MODE. Frames per second: %d Vertices: %d", fps, _vertices);
  #else
  sprintf(f, "Frames per second: %d Vertices: %d", fps, _vertices);
  #endif

  SDL_Surface* fpsSurf;
  SDL_Color c = {255, 255, 255, 0};
  SDL_Rect r;
  r.x = 5;
  r.y = 5;

  #ifdef _DEBUG
  _pfManager.getInstance().start("Drawing");
  #endif
  if(_engineState == GAME_STATE) {
    for(Sint16 i = 0; i < _window.width; i++)
      for(Sint16 j = 0; j < _window.height; j++)
        Draw_Pixel(_screen, i, j, _zbuffer[i][j].color);
  }

  #ifdef _DEBUG
  _pfManager.getInstance().stop("Drawing");
  if(_engineState == MAIN_MENU_STATE) {
    if(_pfManager.getInstance().saved()) {
      static SDL_Rect r;
      r.x = 30;
      r.y = 70;
      SDL_BlitSurface(_pfRegistred, NULL, _screen, &r);
    }
  }
  #endif

  fpsSurf = TTF_RenderUTF8_Blended(_font, f, c);
  SDL_BlitSurface(fpsSurf, NULL, _screen, &r);

  SDL_FreeSurface(fpsSurf);

  //Flip buffers
  SDL_Flip(_screen);
}

void Engine::setColor(float r, float g, float b, float a)
{
  if(r > 1.0f)
    _currentColor.r = 1.0f;
  else if(r < 0.0f)
    _currentColor.r = 0;
  else
    _currentColor.r = r;

  if(g > 1.0f)
    _currentColor.g = 1.0f;
  else if(g < 0.0f)
    _currentColor.g = 0;
  else
    _currentColor.g = g;

  if(b > 1.0f)
    _currentColor.b = 1.0f;
  else if(b < 0.0f)
    _currentColor.b = 0;
  else
    _currentColor.b = b;

  if(a > 1.0f)
    _currentColor.a = 1.0f;
  else if(a < 0.0f)
    _currentColor.a = 0;
  else
    _currentColor.a = a;
}

void Engine::addVertex(float x, float y, float z)
{

  Vector tmp(x, y, z);

  //Get coordiantes in world space;
  tmp = _modelviewMatrix * tmp;

  Vertex2_t vtmp;
  vtmp.color = _currentColor;
  vtmp.point.x = tmp[0];
  vtmp.point.y = tmp[1];
  vtmp.point.z = tmp[2];

  _vertexList.push_back(vtmp);
}

void Engine::getFaceLightCoficient(Face_t& face, float& c)
{
  Vector center((face.a.point.x + face.b.point.x + face.c.point.x) / 3.0,
                (face.a.point.y + face.b.point.y + face.c.point.y) / 3.0,
                (face.a.point.z + face.b.point.z + face.c.point.z) / 3.0 + _perspectiveRatio);

  center.normalize();

  Vector v1(face.a.point.x - face.b.point.x, face.a.point.y - face.b.point.y,
            face.a.point.z - face.b.point.z);
  Vector v2(face.a.point.x - face.c.point.x, face.a.point.y - face.c.point.y,
            face.a.point.z - face.c.point.z);

  Vector normal = v1.cross(v2);
  normal.normalize();

  c = normal.dot(center);
}

void Engine::processLight(Face_t& face)
{
  float a;
  getFaceLightCoficient(face, a);

  a = fabs(a);

  face.a.color.r *= (_lightCoficient * a);
  face.a.color.g *= (_lightCoficient * a);
  face.a.color.b *= (_lightCoficient * a);

  face.b.color.r *= (_lightCoficient * a);
  face.b.color.g *= (_lightCoficient * a);
  face.b.color.b *= (_lightCoficient * a);

  face.c.color.r *= (_lightCoficient * a);
  face.c.color.g *= (_lightCoficient * a);
  face.c.color.b *= (_lightCoficient * a);
}

void Engine::processDrawing()
{
  //Draw nothing if render list is empty
  if(_vertexList.empty())
    return;

  int size = _vertexList.size();

  _vertices = size;

  Face_t currFace;

  if(_triangleMode == TRIANGLE_NORMAL) {

    //We draw only triangles!
    if(size % 3 != 0) {
      _vertexList.clear();
      return;
    }

    Vertex2_t v1, v2, v3;

    for(int i = 0; i < size; i += 3){

      v1 = _vertexList.front();
      _vertexList.pop_front();

      v2 = _vertexList.front();
      _vertexList.pop_front();

      v3 = _vertexList.front();
      _vertexList.pop_front();

      currFace.a = v1;
      currFace.b = v2;
      currFace.c = v3;
      if(_enableLight)
        processLight(currFace);
      drawTriangle(currFace);
      }
    } else if(_triangleMode == TRIANGLE_STRIP) {

      //We draw only triangles!
      if(size % 4 != 0) {
        _vertexList.clear();
        return;
      }

    Vertex2_t v1, v2, v3, v4;

    for(int i = 0; i < size; i += 4){

      v1 = _vertexList.front();
      _vertexList.pop_front();

      v2 = _vertexList.front();
      _vertexList.pop_front();

      v3 = _vertexList.front();
      _vertexList.pop_front();

      v4 = _vertexList.front();
      _vertexList.pop_front();

      currFace.a = v1;
      currFace.b = v2;
      currFace.c = v3;
      if(_enableLight)
        processLight(currFace);
      drawTriangle(currFace);

      currFace.a = v2;
      currFace.b = v3;
      currFace.c = v4;
      if(_enableLight)
        processLight(currFace);
      drawTriangle(currFace);
      }
    }

  _vertexList.clear();
}

void Engine::handleInput(SDL_Event& event, int& buttonIndicator)
{
  if(event.type == SDL_QUIT)
    _isRunning = false;

  if(_engineState == MAIN_MENU_STATE) {

    if(event.type == SDL_KEYDOWN)
      if(event.key.keysym.sym == SDLK_ESCAPE)
        _isRunning = false;

    int button;
    _menu->handleInput(event, button);
    if(button == 1){
      _engineState = GAME_STATE;
      buttonIndicator = BUTTON_CUBE;
    }else if(button == 2){
      _engineState = GAME_STATE;
      buttonIndicator = BUTTON_PYRAMID;
    }else if(button == 3){
      _isRunning = false;
    }
    #ifdef _DEBUG
    else if(button == 4) {

      _pfManager.getInstance().print();
    }
    #endif

  } else if (_engineState == GAME_STATE) {
    if(event.type == SDL_KEYDOWN) {
      if(event.key.keysym.sym == SDLK_ESCAPE){
        _engineState = MAIN_MENU_STATE;
        buttonIndicator = BUTTON_INTERUPT;
        loadIdentity();
      }if(event.key.keysym.sym == SDLK_w) {
        (_renderMode == RENDER_FILLED) ? _renderMode = RENDER_LINES : _renderMode = RENDER_FILLED;
      }
      if(event.key.keysym.sym == SDLK_l) {
        _enableLight = !_enableLight;
      }
    }
  }
}

bool Engine::isRunning() const
{
  return _isRunning;
}

void Engine::setRenderMode(int mode)
{
  if(mode == RENDER_FILLED)
    _renderMode = RENDER_FILLED;
  else if(mode == RENDER_LINES)
    _renderMode = RENDER_LINES;
  else
    _renderMode = RENDER_LINES;
}

void Engine::setTriangleMode(int mode)
{
  if(mode == TRIANGLE_NORMAL)
    _triangleMode = TRIANGLE_NORMAL;
  else if(mode == TRIANGLE_STRIP)
    _triangleMode = TRIANGLE_STRIP;
  else
    _triangleMode = TRIANGLE_NORMAL;
}

void Engine::project(const Vertex2_t& p3d, Point2_t& p2d) const
{
  float scale = _perspectiveRatio / (_perspectiveRatio + p3d.point.z);

  p2d.x = static_cast<Sint16>(p3d.point.x * scale);
  p2d.y = static_cast<Sint16>((_window.height - p3d.point.y) * scale);

  p2d.z = 1.0 / (_perspectiveRatio + p3d.point.z);

  p2d.color = p3d.color;

}

void Engine::drawTriangle(Face_t& face)
{
  //project points
  Point2_t A, B, C;
  project(face.a, A);
  project(face.b, B);
  project(face.c, C);

  if(triangleInView(A, B, C) == false)
    return;

  if(_renderMode == RENDER_FILLED) {
    //Sort points by y
    if(A.y > B.y) {
      swap<Point2_t>(A, B);
    }

    if(A.y > C.y) {
      swap<Point2_t>(A, C);
    }

    if(B.y > C.y) {
      swap<Point2_t>(B, C);
    }

    Sint16 dx1, dx2, dx3;
    dx1 = C.x - A.x;
    dx2 = C.x - B.x;
    dx3 = B.x - A.x;

    Sint16 dy1, dy2, dy3;
    (A.y == C.y) ? dy1 = 1 : dy1 = C.y - A.y;
    (C.y == B.y) ? dy2 = 1 : dy2 = C.y - B.y;
    (B.y == A.y) ? dy3 = 1 : dy3 = B.y - A.y;

    float dz1, dz2, dz3;
    dz1 = C.z - A.z;
    dz2 = C.z - B.z;
    dz3 = B.z - A.z;

    float dr1, dr2, dr3;
    float dg1, dg2, dg3;
    float db1, db2, db3;

    dr1 = (C.color.r - A.color.r) / dy1;
    dg1 = (C.color.g - A.color.g) / dy1;
    db1 = (C.color.b - A.color.b) / dy1;

    dr2 = (C.color.r - B.color.r) / dy2;
    dg2 = (C.color.g - B.color.g) / dy2;
    db2 = (C.color.b - B.color.b) / dy2;

    dr3 = (B.color.r - A.color.r) / dy3;
    dg3 = (B.color.g - A.color.g) / dy3;
    db3 = (B.color.b - A.color.b) / dy3;

    Sint16 y, x1, x2;
    float z1, z2;

    Color4_t col1, col2;

    for(y = A.y; y <= C.y; y++) {
      x1 = A.x + dx1 * (y - A.y) / dy1;

      /* Start of float operations, must be optimized somehow. */
      z1 = A.z + dz1 * (y - A.y) / dy1;

      col1.r = A.color.r + dr1 * (y - A.y);
      col1.g = A.color.g + dg1 * (y - A.y);
      col1.b = A.color.b + db1 * (y - A.y);
      /* end of float operations. */

      if(y >= B.y) {
        x2 = B.x + dx2 * (y - B.y) / dy2;

        /* Start of float operations, must be optimized somehow. */
        z2 = B.z + dz2 * (y - B.y) / dy2;

        col2.r = B.color.r + dr2 * (y - B.y);
        col2.g = B.color.g + dg2 * (y - B.y);
        col2.b = B.color.b + db2 * (y - B.y);
        /* end of float operations. */
      } else {
        x2 = A.x + dx3 * (y - A.y) / dy3;

        /* Start of float operations, must be optimized somehow. */
        z2 = A.z + dz3 * (y - A.y) / dy3;

        col2.r = A.color.r + dr3 * (y - A.y);
        col2.g = A.color.g + dg3 * (y - A.y);
        col2.b = A.color.b + db3 * (y - A.y);
        /* end of float operations. */
      }

      //x1 left x2 right, swap them if its incorrect
      if(x1 > x2) {
        swap<Sint16>(x1 ,x2);
        swap<float>(z1, z2);
        swap<Color4_t>(col1, col2);
      }
      drawHorizLine(x1, x2, y, col1, col2, z1, z2);
    }
  } else if(_renderMode == RENDER_LINES) {
    drawLine(A.x, A.y, B.x, B.y, A.color);
    drawLine(B.x, B.y, C.x, C.y, B.color);
    drawLine(C.x, C.y, A.x, A.y, C.color);
  }
}

void Engine::drawHorizLine(Sint16 x1, Sint16 x2, Sint16 y, Color4_t color1, Color4_t color2,
                           float z1, float z2)
{
  Sint16 i;

  Sint16 dx;
  float dz;

  (x1 == x2) ? dx = 1 : dx = x2 - x1;
  dz = z2 - z1;

  float dr, dg, db;
  dr = (color2.r - color1.r) / dx;
  dg = (color2.g - color1.g) / dx;
  db = (color2.b - color1.b) / dx;

  float z;
  Color4_t finalColor;

  for(i = x1; i <= x2; i++) {
    /* Start of float operations, must be optimized somehow. */
    z = z1 + dz * (i - x1) / dx;

    finalColor.r = color1.r + dr * (i - x1);
    finalColor.g = color1.g + dg * (i - x1);
    finalColor.b = color1.b + db * (i - x1);
    /* end of float operations. */

    putPixel(i, y, finalColor, z);
  }
}

void Engine::drawLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Color4_t color)
{
  Sint16 dx = abs(x2 - x1);
  Sint16 dy = abs(y2 - y1);
  Sint16 x = x1;
  Sint16 y = y1;
  Sint16 den, num, numadd, numpixels; //help vars

  Sint16 xinc1, xinc2, yinc1, yinc2;

  if(x2 >= x1) //X increases
    xinc1 = xinc2 = 1;
  else //X decreases
    xinc1 = xinc2 = -1;

  if(y2 >= y1) //Y increases
    yinc1 = yinc2 = 1;
  else //Y decreases
    yinc1 = yinc2 = -1;

  if(dx >= dy) {//There is at least one x-value for every y-value
    xinc1 = yinc2 = 0;
    den = dx;
    num = dx / 2;
    numadd = dy;
    numpixels = dx;
  } else {
    xinc2 = yinc1 = 0;
    den = dy;
    num = dy / 2;
    numadd = dx;
    numpixels = dy;
  }

  for(Sint16 px = 0; px <= numpixels; px++) {
    putPixel(x, y, color);

    num += numadd;
    if(num >= den) {
      num -= den;
      x += xinc1;
      y += yinc1;
    }
    x += xinc2;
    y += yinc2;
  }
}

void Engine::putPixel(Sint16 x, Sint16 y, Color4_t color, float z)
{
  Uint8 r = static_cast<Uint8>(color.r * 255.0);
  Uint8 g = static_cast<Uint8>(color.g * 255.0);
  Uint8 b = static_cast<Uint8>(color.b * 255.0);

  Uint32 cl = SDL_MapRGB(_screen->format, r, g, b);

  if(pointInView(x, y)) {
    if(_zbuffer[x][y].z <= z) {
      _zbuffer[x][y].z = z;
      _zbuffer[x][y].color = cl;
    }
  }
}

void Engine::putPixel(Sint16 x, Sint16 y, Color4_t color)
{
  Uint8 r = static_cast<Uint8>(color.r * 255.0);
  Uint8 g = static_cast<Uint8>(color.g * 255.0);
  Uint8 b = static_cast<Uint8>(color.b * 255.0);

  Uint32 cl = SDL_MapRGB(_screen->format, r, g, b);

  if(pointInView(x, y)) {
    _zbuffer[x][y].color = cl;
  }
}

bool Engine::pointInView(Sint16 x, Sint16 y) const
{
  return ((x > 0) && (x < _window.width) && (y > 0) && (y < _window.height));
}

bool Engine::triangleInView(Point2_t& p1, Point2_t& p2, Point2_t& p3) const
{
  return (pointInView(p1.x, p1.y) || pointInView(p2.x, p2.y) || pointInView(p3.x, p3.y));
}
