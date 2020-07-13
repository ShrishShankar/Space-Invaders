#ifndef Game_H
#define Game_H

// Including the SDL libraries
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
  void partialInit();

  // Made for the restart mechanism
  // void Restart();
  // void partialClean();

  /**
   * This function returns if the game is running or not.
   *@return 1 if the game is running and 0 if the game is not running.
   */
  bool running() { return isRunning; }

  static SDL_Renderer *renderer;
  // Declaring the renderer as public, because other classes are using it.

  static int screenWidth, screenHeight;
  int windowWidth, windowHeight;
  int frameCount;
  int playerScore{0};

  // One of the components for restarting the game.
  // bool isStart{true};

private:
  bool isRunning{1};
  SDL_Window *window;
};

#endif // Game_H