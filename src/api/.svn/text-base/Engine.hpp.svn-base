/**
* @file Engine.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of engine class.
* This class is the core of the system
*/

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <list>

#include <SDL/SDL_ttf.h>

#include "../Math/Matrix.hpp"
#include "../Math/Vector.hpp"
#include "../gui/MainMenu.hpp"

#ifdef _DEBUG
#include "../utils/Profiler.hpp"
#endif

//3d Point
typedef struct{
  float x, y, z;
}Point3_t;

//Color with 4 components (+alpha)
typedef struct{
  float r, g, b, a;
}Color4_t;

//point
typedef struct{
  Sint16 x, y;
  Color4_t color;
  float z;
}Point2_t;

//Vertex
typedef struct{
  Point3_t point;
  Color4_t color;
}Vertex2_t;

//Face
typedef struct{
  Vertex2_t a, b, c;
}Face_t;

//Zbufer
typedef struct{
  float z;
  Uint32 color;
}ZBuffer_t;

//Vertex list
typedef std::list<Vertex2_t> Vertex2List;

class Engine{
  public:

    /** Engine state enum. */
    enum{
      MAIN_MENU_STATE,
      GAME_STATE
    }eState;

    /** Render mode. */
    enum{
      RENDER_FILLED,
      RENDER_LINES
    }eRenderMode;

    /** Triangle mode. */
    enum{
      TRIANGLE_NORMAL,
      TRIANGLE_STRIP
    }eTriangleMode;

    /** Button indicator enum */
    enum{
      BUTTON_CUBE = 1,
      BUTTON_PYRAMID = 2,
      BUTTON_INTERUPT = 3
    }eButtonIndicator;

    /** Constructor. Initialize the core components.
    * @param width Width of screen (default=800).
    * @param height Height of screen (default=600).
    * @param bpp Bits per pixel (default=32).
    * @param fullscreen Enable/disable fullscreen (default=false).
    */
    Engine(int width = 800, int height = 600, int bpp = 32, bool fullscreen = false);

    /** Destructor. Shutdown all core components. */
    ~Engine();


    /** @defgroup Engine Matrix related operations
    * @{ */

    /** Load identity matrix. */
    void loadIdentity();

    /** Translate.
    * @param dx X translation.
    * @param dy Y translation.
    * @param dz Z translation.
    */
    void translate(float dx, float dy, float dz);

    /** Rotate.
    * @param angle Angle of rotation.
    * @param x/y/z Axis of rotation.
    */
    void rotate(float angle, int x, int y, int z);
    /** @} */

    /** Clear screen.
    * @param color Color to clear with.
    */
    void clearScreen();

    /** Clear z buffer. */
    void clearZbuffer();

    /** Update screen. */
    void updateScreen();

    /** Set drawing color.
    * @param r Red.
    * @param g Green.
    * @param b Blue.
    * @param a Alpha.
    */
    void setColor(float r, float g, float b, float a = 1.0f);

    /** Add new vertex to render list.
    * @param x Vertex x coord.
    * @param y Vertex y coord.
    * @param z Vertex z coord.
    */
    void addVertex(float x, float y, float z);

    /** Handle Input.
    * @param event Event queue.
    * @param buttonIndicator Indicates what button pressed.
    */
    void handleInput(SDL_Event& event, int& buttonIndicator);

    /** @return if engine is running. */
    bool isRunning() const;

    /** Set render mode. Filled on lines. */
    void setRenderMode(int mode);

    /** Set triangle mode, normal or strip. */
    void setTriangleMode(int mode);

  private:
    /** Process Drawing. */
    void processDrawing();

    /** Project.
    * @param p3d 3D point to project.
    * @param p2d Projected 2D point.
    */
    void project(const Vertex2_t& p3d, Point2_t& p2d) const;

    /** Draw triangle.
    * @param screen Buffer to draw to.
    * @param p1 First triangle point.
    * @param p2 Second triangle point.
    * @param p3 Third triangle point.
    * @param color1 Color of first point.
    * @param color2 Color of second point.
    * @param color3 Color of third point.
    */
    void drawTriangle(Face_t& face);

    /** Draw horizontal line.
    * @param x1 First x.
    * @param x2 Second x.
    * @param y Y.
    * @param color1 First color.
    */
    void drawHorizLine(Sint16 x1, Sint16 x2, Sint16 y, Color4_t color1, Color4_t color2,
                       float z1, float z2);

    /** Draw line.
    * @param x1 First x.
    * @param y1 First y.
    * @param x2 Second x.
    * @param y2 Second y.
    * @param color1 First color.
    */
    void drawLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Color4_t color);

    /** Put Pixel.
    * @param x X coord.
    * @param y Y coord.
    * @param color Color.
    */
    void putPixel(Sint16 x, Sint16 y, Color4_t color, float z);
    void putPixel(Sint16 x, Sint16 y, Color4_t color);

    /** Check if point in view.
    * @param x xCoord.
    * @param y yCoord.
    * @return true if point in view otherwise false.
    */
    bool pointInView(Sint16 x, Sint16 y) const;

    /** Check if triangle in view.
    * @param p1 first veretx.
    * @param p2 second veretx.
    * @param p3 third veretx.
    */
    bool triangleInView(Point2_t& p1, Point2_t& p2, Point2_t& p3) const;

    /** Proccess Lightiht on each face.
    * @param face Face to proccess light on it.
    */
    void processLight(Face_t& face);

    /** Get light cooficient for specific face.
    * @param face Face to get light coficient to.
    * @param c Reference to save coficient into.
    */
    void getFaceLightCoficient(Face_t& face, float& c);

    template<typename T>
    void swap(T& p1, T& p2)
    {
      T temp;
      temp = p1;
      p1 = p2;
      p2 = temp;
    }

    struct{
      int width; /**< Screen width */
      int height; /**< Screen height. */
      int bpp; /**< Screen bits per pixel. */
      bool fullscreen; /**< Enable/Disable full screen .*/
    }_window; /**< Screen info. */

    Matrix _modelviewMatrix; /**< Model view matrix. */

    Color4_t _currentColor; /**< Current drawing color. */
    Uint32 _clearColor; /**< Color to clear the screen with. */

    float _perspectiveRatio; /**< Perspective ratio. */

    SDL_Surface* _screen; /**< Screen surface. */

    Vertex2List _vertexList; /**< List of vertices to render. */

    int _engineState; /**< State of engine. */

    TTF_Font* _font; /**< Font. */

    MainMenu* _menu; /**< Menu. */

    bool _isRunning; /**< Is engine running. */

    SDL_Surface* _menuBg; /**< Menu background image. */

    float _lastTime; /**< Used for fps. */

    ZBuffer_t** _zbuffer; /**< Z-Buffer. */

    int _renderMode; /**< Render mode. */
    int _triangleMode; /**< Triangle Mode. */

    bool _enableLight; /**< Enable/disbale light indicator. */
    float _lightCoficient; /**< Light coficient. */

    int _vertices; /**< Num vertices. */

    #ifdef _DEBUG
    ProfileManager _pfManager;
    SDL_Surface* _pfRegistred;
    #endif
    SDL_Surface* _credit; /**< Credits. */
};

#endif // ENGINE_HPP_INCLUDED
