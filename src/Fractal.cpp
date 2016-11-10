/**
* @file Fractal.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of fractal class.
*/

#include "Fractal.hpp"

/**
* Copy lists, copy one list to antoher
*/
void copyList(FractalList& from, FractalList& to)
{
  FractalListIter iter;
  to.clear();
  for(iter = from.begin(); iter != from.end(); ++iter)
    to.push_back(*iter);
}

/**
* Copy pyramid lists, copy one list to antoher
*/
void copyPyrList(FractalPyrList& from, FractalPyrList& to)
{
  FractalPyrListIter iter;
  to.clear();
  for(iter = from.begin(); iter != from.end(); ++iter)
    to.push_back(*iter);
}

//Fractal cube constructor
FractalCube::FractalCube()
{
  _fractalCubesList.clear();

  size = 180.0f;
  _level = 1;
  _inverse = false;
  makeBaseFractal();
}

//Faractal cube destructor
FractalCube::~FractalCube()
{
  _fractalCubesList.clear();
}

//Render cube
void FractalCube::render(Engine& renderer)
{
  renderer.setTriangleMode(Engine::TRIANGLE_STRIP);
  FractalListIter iter;

  for(iter = _fractalCubesList.begin(); iter != _fractalCubesList.end(); ++iter)
    drawCube(renderer, *iter);
}

//Handle input
void FractalCube::handleInput(SDL_Event& event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_SPACE)
      addLevel();
  }
}

//Add level
void FractalCube::addLevel()
{
  if(!_inverse) {
    if(_level > 3)
      return;
  } else {
    if(_level > 4)
      return;
  }

  FractalList temp;
  copyList(_fractalCubesList, temp);
  _fractalCubesList.clear();

  FractalListIter iter;
  for(iter = temp.begin(); iter != temp.end(); ++iter)
    analyzeCube(*iter);

  temp.clear();
  _level++;
}

//Analyze cube, very hard algorithm :/
void FractalCube::analyzeCube(FractalCube_t& cube)
{
  //size of new cube is 3 times smaller then the originals one
  float size = cube.size / 3.0f;
  //Temp cube
  FractalCube_t nCube;
  //Set misc parameters
  nCube.size = size;
  float sizex, sizey, sizez;
  sizex = sizey = sizez = size;
  float startpx, startpy, startpz;
  startpx = cube.f[0].a.x;
  startpy = cube.f[0].a.y;
  startpz = cube.f[0].a.z;

  for(int zi = 0; zi < 3; zi++) {
    for(int yi = 0; yi < 3; yi++) {
      for(int xi = 0; xi < 3; xi++) {
        if(_inverse) {
          if(!(((yi == 1) && (xi == 1)) || ((yi == 1) && (zi == 1)) || ((xi == 1) && (zi == 1))))
            continue;
        } else {
          if((((yi == 1) && (xi == 1)) || ((yi == 1) && (zi == 1)) || ((xi == 1) && (zi == 1))))
            continue;
        }

        //Front
        nCube.f[0].a.x = startpx + sizex * xi;
        nCube.f[0].a.y = startpy - sizey * yi;
        nCube.f[0].a.z = startpz + sizez * zi;

        nCube.f[0].b.x = nCube.f[0].a.x;
        nCube.f[0].b.y = nCube.f[0].a.y - sizey;
        nCube.f[0].b.z = nCube.f[0].a.z;

        nCube.f[0].c.x = nCube.f[0].a.x + sizex;
        nCube.f[0].c.y = nCube.f[0].a.y;
        nCube.f[0].c.z = nCube.f[0].a.z;

        nCube.f[0].d.x = nCube.f[0].a.x + sizex;
        nCube.f[0].d.y = nCube.f[0].a.y - sizey;
        nCube.f[0].d.z = nCube.f[0].a.z;

        //Back
        nCube.f[1].a.x = nCube.f[0].a.x;
        nCube.f[1].a.y = nCube.f[0].a.y;
        nCube.f[1].a.z = nCube.f[0].a.z + sizez;

        nCube.f[1].b.x = nCube.f[0].b.x;
        nCube.f[1].b.y = nCube.f[0].b.y;
        nCube.f[1].b.z = nCube.f[0].b.z + sizez;

        nCube.f[1].c.x = nCube.f[0].c.x;
        nCube.f[1].c.y = nCube.f[0].c.y;
        nCube.f[1].c.z = nCube.f[0].c.z + sizez;

        nCube.f[1].d.x = nCube.f[0].d.x;
        nCube.f[1].d.y = nCube.f[0].d.y;
        nCube.f[1].d.z = nCube.f[0].d.z + sizez;

        //Top
        nCube.f[2].a.x = nCube.f[1].a.x;
        nCube.f[2].a.y = nCube.f[1].a.y;
        nCube.f[2].a.z = nCube.f[1].a.z;

        nCube.f[2].b.x = nCube.f[0].a.x;
        nCube.f[2].b.y = nCube.f[0].a.y;
        nCube.f[2].b.z = nCube.f[0].a.z;

        nCube.f[2].c.x = nCube.f[1].c.x;
        nCube.f[2].c.y = nCube.f[1].c.y;
        nCube.f[2].c.z = nCube.f[1].c.z;

        nCube.f[2].d.x = nCube.f[0].c.x;
        nCube.f[2].d.y = nCube.f[0].c.y;
        nCube.f[2].d.z = nCube.f[0].c.z;

        //Bottom
        nCube.f[3].a.x = nCube.f[2].a.x;
        nCube.f[3].a.y = nCube.f[2].a.y - sizey;
        nCube.f[3].a.z = nCube.f[2].a.z;

        nCube.f[3].b.x = nCube.f[2].b.x;
        nCube.f[3].b.y = nCube.f[2].b.y - sizey;
        nCube.f[3].b.z = nCube.f[2].b.z;

        nCube.f[3].c.x = nCube.f[2].c.x;
        nCube.f[3].c.y = nCube.f[2].c.y - sizey;
        nCube.f[3].c.z = nCube.f[2].c.z;

        nCube.f[3].d.x = nCube.f[2].d.x;
        nCube.f[3].d.y = nCube.f[2].d.y - sizey;
        nCube.f[3].d.z = nCube.f[2].d.z;

        //Left
        nCube.f[4].a.x = nCube.f[1].a.x;
        nCube.f[4].a.y = nCube.f[1].a.y;
        nCube.f[4].a.z = nCube.f[1].a.z;

        nCube.f[4].b.x = nCube.f[1].b.x;
        nCube.f[4].b.y = nCube.f[1].b.y;
        nCube.f[4].b.z = nCube.f[1].b.z;

        nCube.f[4].c.x = nCube.f[0].a.x;
        nCube.f[4].c.y = nCube.f[0].a.y;
        nCube.f[4].c.z = nCube.f[0].a.z;

        nCube.f[4].d.x = nCube.f[0].b.x;
        nCube.f[4].d.y = nCube.f[0].b.y;
        nCube.f[4].d.z = nCube.f[0].b.z;

        //Right
        nCube.f[5].a.x = nCube.f[4].a.x + sizex;
        nCube.f[5].a.y = nCube.f[4].a.y;
        nCube.f[5].a.z = nCube.f[4].a.z;

        nCube.f[5].b.x = nCube.f[4].b.x + sizex;
        nCube.f[5].b.y = nCube.f[4].b.y;
        nCube.f[5].b.z = nCube.f[4].b.z;

        nCube.f[5].c.x = nCube.f[4].c.x + sizex;
        nCube.f[5].c.y = nCube.f[4].c.y;
        nCube.f[5].c.z = nCube.f[4].c.z;

        nCube.f[5].d.x = nCube.f[4].d.x + sizex;
        nCube.f[5].d.y = nCube.f[4].d.y;
        nCube.f[5].d.z = nCube.f[4].d.z;

        nCube.f[0].color = cube.f[0].color;
        nCube.f[1].color = cube.f[1].color;
        nCube.f[2].color = cube.f[2].color;
        nCube.f[3].color = cube.f[3].color;
        nCube.f[4].color = cube.f[4].color;
        nCube.f[5].color = cube.f[5].color;

        _fractalCubesList.push_back(nCube);
      }
    }
  }
}

//Draw cube
void FractalCube::drawCube(Engine& renderer, const FractalCube_t& cube)
{
  for(int i = 0; i < 6; i++) {
    renderer.setColor(cube.f[i].color.r, cube.f[i].color.g, cube.f[i].color.b);
    renderer.addVertex(cube.f[i].a.x, cube.f[i].a.y, cube.f[i].a.z);
    renderer.addVertex(cube.f[i].b.x, cube.f[i].b.y, cube.f[i].b.z);
    renderer.addVertex(cube.f[i].c.x, cube.f[i].c.y, cube.f[i].c.z);
    renderer.addVertex(cube.f[i].d.x, cube.f[i].d.y, cube.f[i].d.z);
  }
}

//Make base cube
void FractalCube::makeBaseFractal()
{
  FractalCube_t cube;
  //Back
  cube.f[0].a.x = -size; cube.f[0].a.y =  size; cube.f[0].a.z = -size;
  cube.f[0].b.x = -size; cube.f[0].b.y = -size; cube.f[0].b.z = -size;
  cube.f[0].c.x =  size; cube.f[0].c.y =  size; cube.f[0].c.z = -size;
  cube.f[0].d.x =  size; cube.f[0].d.y = -size; cube.f[0].d.z = -size;
  cube.f[0].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[0].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[0].color.b = float((rand() % 200 + 50) / 255.0);

  //Front
  cube.f[1].a.x = -size; cube.f[1].a.y =  size; cube.f[1].a.z = size;
  cube.f[1].b.x = -size; cube.f[1].b.y = -size; cube.f[1].b.z = size;
  cube.f[1].c.x =  size; cube.f[1].c.y =  size; cube.f[1].c.z = size;
  cube.f[1].d.x =  size; cube.f[1].d.y = -size; cube.f[1].d.z = size;
  cube.f[1].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[1].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[1].color.b = float((rand() % 200 + 50) / 255.0);

  //Up
  cube.f[2].a.x = -size; cube.f[2].a.y =  size; cube.f[2].a.z = -size;
  cube.f[2].b.x = -size; cube.f[2].b.y =  size; cube.f[2].b.z =  size;
  cube.f[2].c.x =  size; cube.f[2].c.y =  size; cube.f[2].c.z = -size;
  cube.f[2].d.x =  size; cube.f[2].d.y =  size; cube.f[2].d.z =  size;
  cube.f[2].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[2].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[2].color.b = float((rand() % 200 + 50) / 255.0);

  //Down
  cube.f[3].a.x = -size; cube.f[3].a.y = -size; cube.f[3].a.z = -size;
  cube.f[3].b.x = -size; cube.f[3].b.y = -size; cube.f[3].b.z =  size;
  cube.f[3].c.x =  size; cube.f[3].c.y = -size; cube.f[3].c.z = -size;
  cube.f[3].d.x =  size; cube.f[3].d.y = -size; cube.f[3].d.z =  size;
  cube.f[3].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[3].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[3].color.b = float((rand() % 200 + 50) / 255.0);

  //Left
  cube.f[4].a.x = -size; cube.f[4].a.y =  size; cube.f[4].a.z =  size;
  cube.f[4].b.x = -size; cube.f[4].b.y = -size; cube.f[4].b.z =  size;
  cube.f[4].c.x = -size; cube.f[4].c.y =  size; cube.f[4].c.z = -size;
  cube.f[4].d.x = -size; cube.f[4].d.y = -size; cube.f[4].d.z = -size;
  cube.f[4].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[4].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[4].color.b = float((rand() % 200 + 50) / 255.0);

  //Right
  cube.f[5].a.x =  size; cube.f[5].a.y =  size; cube.f[5].a.z =  size;
  cube.f[5].b.x =  size; cube.f[5].b.y = -size; cube.f[5].b.z =  size;
  cube.f[5].c.x =  size; cube.f[5].c.y =  size; cube.f[5].c.z = -size;
  cube.f[5].d.x =  size; cube.f[5].d.y = -size; cube.f[5].d.z = -size;
  cube.f[5].color.r = float((rand() % 200 + 50) / 255.0);
  cube.f[5].color.g = float((rand() % 200 + 50) / 255.0);
  cube.f[5].color.b = float((rand() % 200 + 50) / 255.0);

  cube.size = 2.0f * size;

  _fractalCubesList.push_back(cube);
}



//Pyramid constructor
FractalPyramid::FractalPyramid()
{
  _fractalPyramidsList.clear();

  size = 120.0f;
  _level = 1;
  _inverse = false;

  makeBaseFractal();
}

//Pyramid destructor
FractalPyramid::~FractalPyramid()
{
  _fractalPyramidsList.clear();
}

//Render pyramid
void FractalPyramid::render(Engine& renderer)
{
  renderer.setTriangleMode(Engine::TRIANGLE_NORMAL);
  FractalPyrListIter iter;
  BaseListIter bIter;

  for(bIter = _baseList.begin(); bIter != _baseList.end(); ++bIter)
    drawBase(renderer, *bIter);

  for(iter = _fractalPyramidsList.begin(); iter != _fractalPyramidsList.end(); ++iter)
    drawPyramid(renderer, *iter);
}


//hanlde pyramid input
void FractalPyramid::handleInput(SDL_Event& event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_SPACE)
      addLevel();
  }
}

//Add new level
void FractalPyramid::addLevel()
{
  if(!_inverse) {
    if(_level > 6)
      return;
  } else {
    if(_level > 4)
      return;
  }

  FractalPyrList temp;
  copyPyrList(_fractalPyramidsList, temp);
  _fractalPyramidsList.clear();

  _baseList.clear();
  FractalPyrListIter iter;
  for(iter = temp.begin(); iter != temp.end(); ++iter)
    analyzePyramid(*iter);

  temp.clear();
  _level++;
}

//Analzye pyramid
void FractalPyramid::analyzePyramid(FractalPyramid_t& pyr)
{
  float size = pyr.size / 2.0f;
  FractalPyramid_t nPyr;
  FractalFace_t base;
  nPyr.size = size;
  float sizex, sizey, sizez;
  sizex = sizey = sizez = size;
  float startpx, startpy, startpz;
  startpx = pyr.f[0].a.x;
  startpy = pyr.f[0].a.y;
  startpz = pyr.f[0].a.z;

  for(int i = 1; i <= 5; i++){
    //Face 1
    nPyr.f[0].a.x = startpx;
    nPyr.f[0].a.y = startpy;
    nPyr.f[0].a.z = startpz;
    nPyr.f[0].b.x = nPyr.f[0].a.x - sizex;
    nPyr.f[0].b.y = nPyr.f[0].a.y - sizey;
    nPyr.f[0].b.z = nPyr.f[0].a.z + sizez;
    nPyr.f[0].c.x = nPyr.f[0].a.x + sizex;
    nPyr.f[0].c.y = nPyr.f[0].a.y - sizey;
    nPyr.f[0].c.z = nPyr.f[0].a.z + sizez;

    //Face 2
    nPyr.f[1].a.x = nPyr.f[0].a.x;
    nPyr.f[1].a.y = nPyr.f[0].a.y;
    nPyr.f[1].a.z = nPyr.f[0].a.z;
    nPyr.f[1].b.x = nPyr.f[1].a.x - sizex;
    nPyr.f[1].b.y = nPyr.f[1].a.y - sizey;
    nPyr.f[1].b.z = nPyr.f[1].a.z - sizez;
    nPyr.f[1].c.x = nPyr.f[1].a.x + sizex;
    nPyr.f[1].c.y = nPyr.f[1].a.y - sizey;
    nPyr.f[1].c.z = nPyr.f[1].a.z - sizez;

    //Face 3
    nPyr.f[2].a.x = nPyr.f[0].a.x;
    nPyr.f[2].a.y = nPyr.f[0].a.y;
    nPyr.f[2].a.z = nPyr.f[0].a.z;
    nPyr.f[2].b.x = nPyr.f[2].a.x - sizex;
    nPyr.f[2].b.y = nPyr.f[2].a.y - sizey;
    nPyr.f[2].b.z = nPyr.f[2].a.z + sizez;
    nPyr.f[2].c.x = nPyr.f[2].a.x - sizex;
    nPyr.f[2].c.y = nPyr.f[2].a.y - sizey;
    nPyr.f[2].c.z = nPyr.f[2].a.z - sizez;

    //Face 4
    nPyr.f[3].a.x = nPyr.f[0].a.x;
    nPyr.f[3].a.y = nPyr.f[0].a.y;
    nPyr.f[3].a.z = nPyr.f[0].a.z;
    nPyr.f[3].b.x = nPyr.f[3].a.x + sizex;
    nPyr.f[3].b.y = nPyr.f[3].a.y - sizey;
    nPyr.f[3].b.z = nPyr.f[3].a.z + sizez;
    nPyr.f[3].c.x = nPyr.f[3].a.x + sizex;
    nPyr.f[3].c.y = nPyr.f[3].a.y - sizey;
    nPyr.f[3].c.z = nPyr.f[3].a.z - sizez;

    nPyr.f[0].color = pyr.f[0].color;
    nPyr.f[1].color = pyr.f[1].color;
    nPyr.f[2].color = pyr.f[2].color;
    nPyr.f[3].color = pyr.f[3].color;

    _fractalPyramidsList.push_back(nPyr);

    base.a.x = startpx - sizex;
    base.a.y = startpy - sizey;
    base.a.z = startpz - sizez;
    base.b.x = startpx - sizex;
    base.b.y = startpy - sizey;
    base.b.z = startpz + sizez;
    base.c.x = startpx + sizex;
    base.c.y = startpy - sizey;
    base.c.z = startpz - sizez;
    base.d.x = startpx + sizex;
    base.d.y = startpy - sizey;
    base.d.z = startpz + sizez;
    base.color.r = 0.0;
    base.color.g = 1.0;
    base.color.b = 1.0;

    _baseList.push_back(base);

    if(i == 1){
      startpx -= sizex;
      startpy -= sizey;
      startpz -= sizez;
    }else if(i == 2){
      startpx += 2 * sizex;
    }else if(i == 3){
      startpz += 2 * sizez;
    }else if(i == 4){
      startpx -= 2 * sizex;
    }
  }
}

//Draw single pyramid
void FractalPyramid::drawPyramid(Engine& renderer, const FractalPyramid_t& pyr)
{
  for(int i = 0; i < 4; i++) {
    renderer.setColor(pyr.f[i].color.r, pyr.f[i].color.g, pyr.f[i].color.b);
    renderer.addVertex(pyr.f[i].a.x, pyr.f[i].a.y, pyr.f[i].a.z);
    renderer.addVertex(pyr.f[i].b.x, pyr.f[i].b.y, pyr.f[i].b.z);
    renderer.addVertex(pyr.f[i].c.x, pyr.f[i].c.y, pyr.f[i].c.z);
  }
}

//make base pyramid fractal
void FractalPyramid::makeBaseFractal()
{
  float cof = 1.99f; //correctness cofficient
  FractalPyramid_t pyr;
  FractalFace_t base;

  pyr.f[0].a.x =   0.0; pyr.f[0].a.y =  size; pyr.f[0].a.z =  0.0;
  pyr.f[0].b.x = -cof*size; pyr.f[0].b.y = -size; pyr.f[0].b.z = cof*size;
  pyr.f[0].c.x =  cof*size; pyr.f[0].c.y = -size; pyr.f[0].c.z = cof*size;
  pyr.f[0].color.r = float((rand() % 200 + 50) / 255.0);
  pyr.f[0].color.g = float((rand() % 200 + 50) / 255.0);
  pyr.f[0].color.b = float((rand() % 200 + 50) / 255.0);

  pyr.f[1].a.x =   0.0; pyr.f[1].a.y =  size; pyr.f[1].a.z =   0.0;
  pyr.f[1].b.x = -cof*size; pyr.f[1].b.y = -size; pyr.f[1].b.z = -cof*size;
  pyr.f[1].c.x =  cof*size; pyr.f[1].c.y = -size; pyr.f[1].c.z = -cof*size;
  pyr.f[1].color.r = float((rand() % 200 + 50) / 255.0);
  pyr.f[1].color.g = float((rand() % 200 + 50) / 255.0);
  pyr.f[1].color.b = float((rand() % 200 + 50) / 255.0);

  pyr.f[2].a.x =   0.0; pyr.f[2].a.y =  size; pyr.f[2].a.z =   0.0;
  pyr.f[2].b.x = -cof*size; pyr.f[2].b.y = -size; pyr.f[2].b.z = -cof*size;
  pyr.f[2].c.x = -cof*size; pyr.f[2].c.y = -size; pyr.f[2].c.z =  cof*size;
  pyr.f[2].color.r = float((rand() % 200 + 50) / 255.0);
  pyr.f[2].color.g = float((rand() % 200 + 50) / 255.0);
  pyr.f[2].color.b = float((rand() % 200 + 50) / 255.0);

  pyr.f[3].a.x =  0.0; pyr.f[3].a.y =  size; pyr.f[3].a.z =   0.0;
  pyr.f[3].b.x = cof*size; pyr.f[3].b.y = -size; pyr.f[3].b.z =  cof*size;
  pyr.f[3].c.x = cof*size; pyr.f[3].c.y = -size; pyr.f[3].c.z = -cof*size;
  pyr.f[3].color.r = float((rand() % 200 + 50) / 255.0);
  pyr.f[3].color.g = float((rand() % 200 + 50) / 255.0);
  pyr.f[3].color.b = float((rand() % 200 + 50) / 255.0);

  pyr.size = 2.0f * size;

  base.a.x = -cof*size; base.a.y = -size; base.a.z =  cof*size;
  base.b.x =  cof*size; base.b.y = -size; base.b.z =  cof*size;
  base.c.x = -cof*size; base.c.y = -size; base.c.z = -cof*size;
  base.d.x =  cof*size; base.d.y = -size; base.d.z = -cof*size;
  base.color.r = float((rand() % 200 + 50) / 255.0);
  base.color.g = float((rand() % 200 + 50) / 255.0);
  base.color.b = float((rand() % 200 + 50) / 255.0);

  _baseList.push_back(base);

  _fractalPyramidsList.push_back(pyr);
}

//Draw pyramid's base
void FractalPyramid::drawBase(Engine& renderer, const FractalFace_t& base)
{
  //renderer.setTriangleMode(Engine::TRIANGLE_STRIP);
  renderer.setColor(base.color.r, base.color.g, base.color.b);
  renderer.addVertex(base.a.x, base.a.y, base.a.z);
  renderer.addVertex(base.b.x, base.b.y, base.b.z);
  renderer.addVertex(base.c.x, base.c.y, base.c.z);

  renderer.addVertex(base.b.x, base.b.y, base.b.z);
  renderer.addVertex(base.c.x, base.c.y, base.c.z);
  renderer.addVertex(base.d.x, base.d.y, base.d.z);
}
