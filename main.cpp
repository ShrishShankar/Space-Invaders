/*
Building while viewing the main file gives the correct output.
Building while on anyother file gives the output of the previous build.
Not sure why this happens, mostly it is problem with the way VS code's task.json
builds a project. Running the code using the run button (code runner) gives the
correct output, irrespective of the file currently being viewed.
*/
#include "game.h"

Game *game{nullptr};

const float FPS = 60;
const float mSPF = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(int argc, char *argv[]) {
  game = new Game;

  game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640,
             false);

  while (game->running()) {

    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (mSPF > frameTime) {
      /*
      The desktop's framerate is 60FPS (usually), so if the update (or
      rendering) is faster it looks like the gameobject is jumping instead of
      moving smoothly, because the rendering more than once before the desktop
      frame changes even once.
      */
      SDL_Delay(mSPF - frameTime);
    }
  }

  game->clean();
  delete game;

  return 0;
}