/**
* @file Fractal.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of fractal class.
*/

#ifndef FRACTAL_HPP_INCLUDED
#define FRACTAL_HPP_INCLUDED

#include <list>

#include <SDL/SDL.h>

#include "api/Engine.hpp"

//Fractal cube face
typedef struct{
  Point3_t a, b, c, d;
  Color4_t color;
}FractalFace_t;

//Fractal pyramid face
typedef struct{
  Point3_t a, b, c;
  Color4_t color;
}FractalFacePyr_t;

//fractal cube
typedef struct{
  FractalFace_t f[6]; //faces
  float size;
}FractalCube_t;

//fractal pyramid
typedef struct{
  FractalFacePyr_t f[4];
  float size;
}FractalPyramid_t;

//Fractal cube list
typedef std::list<FractalCube_t> FractalList;
typedef std::list<FractalCube_t>::iterator FractalListIter;

//Fractal pyramid list
typedef std::list<FractalPyramid_t> FractalPyrList;
typedef std::list<FractalPyramid_t>::iterator FractalPyrListIter;

//Fractal pyramid base list
typedef std::list<FractalFace_t> BaseList;
typedef std::list<FractalFace_t>::iterator BaseListIter;

//Copy lists
void copyList(FractalList& from, FractalList& to);
void copyPyrList(FractalPyrList& from, FractalPyrList& to);

class Fractal{
  public:
    virtual void render(Engine& renderer) = 0;
    virtual void handleInput(SDL_Event& event) = 0;

    virtual ~Fractal(){}
};

class FractalCube: public Fractal{
  public:
    /**
    * Dtor
    */
    FractalCube();
    /**
    * ctor
    */
    ~FractalCube();

    /**
    * Render
    * @param renderer Renderer reference.
    */
    void render(Engine& renderer);

    /**
    * Handle input
    * @param event Event list.
    */
    void handleInput(SDL_Event& event);

  private:
    /**
    * Add new level
    */
    void addLevel();

    /**
    * Analzye cube.
    * @param cube Cube to analyze
    */
    void analyzeCube(FractalCube_t& cube);

    /**
    * Draw Cube
    * @param renderer Renderer reference.
    * @param cube Cube to draw
    */
    void drawCube(Engine& renderer, const FractalCube_t& cube);

    /**
    * Make Base cube fracal
    */
    void makeBaseFractal();

    float size; /**< Size of cube */
    int _level; /**< Level */
    bool _inverse;  /**< Deprecated, not used, ignore */

    FractalList _fractalCubesList;  /**< Faracal cube list */
};

class FractalPyramid: public Fractal{
  public:
    /**
    * Dtor
    */
    FractalPyramid();

    /**
    * Ctor
    */
    ~FractalPyramid();

    /**
    * Render
    * @param renderer Renderer reference.
    */
    void render(Engine& renderer);

    /**
    * Handle input
    * @param event Event list.
    */
    void handleInput(SDL_Event& event);

  private:
    /**
    * Add new level
    */
    void addLevel();

    /**
    * Analzye pyramid.
    * @param pyr Pyramid to analyze
    */
    void analyzePyramid(FractalPyramid_t& pyr);

    /**
    * Draw Pyramid
    * @param renderer Renderer reference.
    * @param pyr Pyramid to draw
    */
    void drawPyramid(Engine& renderer, const FractalPyramid_t& pyr);

    /**
    * Make Base cube fracal
    */
    void makeBaseFractal();

    /**
    * Draw Base
    * @param renderer Renderer reference.
    * @param base Base to draw
    */
    void drawBase(Engine& renderer, const FractalFace_t& base);

    float size; /**< Size of puramid */
    int _level; /**< Level */
    bool _inverse;  /**< Deprecated, not used, ignore */

    FractalPyrList _fractalPyramidsList;  /**< Faracal pyramid list */
    BaseList _baseList;   /**< Faracal base list */
};

#endif // FRACTAL_HPP_INCLUDED
