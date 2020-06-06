#ifndef Game_H
#define Game_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreeen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() { return isRunning; }

  static SDL_Renderer *renderer; // declaring a renderer

private:
  bool isRunning;
  SDL_Window *window; // declaraing a window
};

#endif // Game_H