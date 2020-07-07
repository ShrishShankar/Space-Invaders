#ifndef Game_H
#define Game_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Game {
public:
  void init(const char *title, int xpos, int ypos, bool fullscreeen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() { return isRunning; }

  static SDL_Renderer
      *renderer; // declaring a renderer, the renderer is a public variable
                 // because other classes are using it.
  static int screenWidth, screenHeight;

private:
  bool isRunning;
  SDL_Window *window; // declaraing a window
};

#endif // Game_H