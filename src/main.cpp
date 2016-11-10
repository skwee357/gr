#include <iostream>

#include <SDL/SDL.h>

#include "api/Engine.hpp"
#include "utils/Exception.hpp"
#include "Fractal.hpp"

/** Draw Board
* Draw a chess board under the figures
* @param renderer Engine renderer the one that handles rendering
* @param figure Determine what figure we are drawing the bodrd for.
*/
void drawBoard(Engine& renderer, int figure){
  float size = 800; //Half size of board
  float step = 200; //One step

  //If figure is cube draw board using strip triangles
  if(figure == Engine::BUTTON_CUBE){
    float sizey = -182.0;
    renderer.setTriangleMode(Engine::TRIANGLE_STRIP);

    int count = 0;
    for(float i = -size; i <= size; i += step){
      for(float j = -size; j <= size; j += step){
        if(count % 2 == 0)
          renderer.setColor(0.0, 0.0, 0.0);
        else
          renderer.setColor(1.0, 1.0, 1.0);
        renderer.addVertex(i       , sizey, j);
        renderer.addVertex(i + step, sizey, j);
        renderer.addVertex(i       , sizey, j + step);
        renderer.addVertex(i + step, sizey, j + step);
        count++;
      }
    }
  }else if(figure == Engine::BUTTON_PYRAMID){ //If figure is pyramid draw board using normal triangles
    float sizey = -122.0;
    renderer.setTriangleMode(Engine::TRIANGLE_NORMAL);

    int count = 0;
    for(float i = -size; i <= size; i += step){
      for(float j = -size; j <= size; j += step){
        if(count % 2 == 0)
          renderer.setColor(0.0, 0.0, 0.0);
        else
          renderer.setColor(1.0, 1.0, 1.0);
        renderer.addVertex(i       , sizey, j);
        renderer.addVertex(i + step, sizey, j);
        renderer.addVertex(i       , sizey, j + step);

        renderer.addVertex(i + step, sizey, j);
        renderer.addVertex(i       , sizey, j + step);
        renderer.addVertex(i + step, sizey, j + step);
        count++;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  try{

    Engine sk(800, 600, 32);  //Initialize engine
    Fractal* fractal = NULL;
    SDL_Event event;  //Event queue

    //Misc variables
    float ax, ay, az;
    float x, y, z;
    int button;
    ax = ay = az = 0.0f;
    x = y = z = 0.0f;

    srand(time(NULL));

    //Main loop
    while(sk.isRunning()) {
      while(SDL_PollEvent(&event)) {

        //Handle engine input
        sk.handleInput(event, button);

        //Cube button pressed create cube
        if((!fractal) && (button == Engine::BUTTON_CUBE)){
          fractal = new FractalCube;
          ax = ay = az = 0.0f;
          x = y = z = 0.0f;
        }

        //Pyramid button pressed create pyramid
        if((!fractal) && (button == Engine::BUTTON_PYRAMID)){
          fractal = new FractalPyramid;
          ax = ay = az = 0.0f;
          x = y = z = 0.0f;
        }

        //Esc button pressed destroy object
        if((fractal) && (button == Engine::BUTTON_INTERUPT)){
          delete fractal;
          fractal = NULL;
        }

        //Handle fractatl's input
        if(fractal)
          fractal->handleInput(event);

        //Handle other input
        if(event.type == SDL_KEYDOWN) {
          if(event.key.keysym.sym == SDLK_LEFT)
            ay += 5.0f;
          if(event.key.keysym.sym == SDLK_RIGHT)
            ay -= 5.0f;
          if(event.key.keysym.sym == SDLK_UP)
            ax -= 5.0f;
          if(event.key.keysym.sym == SDLK_DOWN)
            ax += 5.0f;
          if(event.key.keysym.sym == SDLK_z)
            az += 5.0f;
          if(event.key.keysym.sym == SDLK_x)
            az -= 5.0f;
          if(event.key.keysym.sym == SDLK_KP_PLUS)
            z += 25.0f;
          if(event.key.keysym.sym == SDLK_KP_MINUS)
            z -= 25.0f;
          if(event.key.keysym.sym == SDLK_KP6)
            x -= 25.0f;
          if(event.key.keysym.sym == SDLK_KP4)
            x += 25.0f;
          if(event.key.keysym.sym == SDLK_KP8)
            y -= 25.0f;
          if(event.key.keysym.sym == SDLK_KP5)
            y += 25.0f;
        }
      }

      if(ax > 359.0f) ax = 0.0f;
      if(ax < 0.0f) ax = 359.0f;

      if(ay > 359.0f) ay = 0.0f;
      if(ay < 0.0f) ay = 359.0f;

      if(az > 359.0f) az = 0.0f;
      if(az < 0.0f) az = 359.0f;

      //Clear screen, zbuffer
      sk.clearScreen();
      sk.clearZbuffer();

      //Load identity matrix, + rotate + translate
      sk.loadIdentity();
      sk.translate(x, y, z);
      sk.rotate(ax, 1, 0, 0);
      sk.rotate(ay, 0, 1, 0);
      sk.rotate(az, 0, 0, 1);

      //Draw board
      drawBoard(sk, button);

      //Draw fractal
      if(fractal)
        fractal->render(sk);

      //Update screen
      sk.updateScreen();
      SDL_Delay(18);
    }

    //Destroy fractal
    if(fractal)
      delete fractal;
  }
  catch(Exception& e){
    std::cout << "Error " << e.what();
  }

  return 0;
}
