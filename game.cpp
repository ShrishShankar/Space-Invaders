#include "game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "map.h"
#include <iostream>
#include <vector>

GameObject *spaceship{NULL};
GameObject *alien{NULL};
std::vector<GameObject *> laser_beams;
Map *map{NULL};

void ToggleFullscreen(SDL_Window *Window) {
  Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
  bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
  SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
  SDL_ShowCursor(IsFullscreen);
}

SDL_Renderer *Game::renderer = nullptr;
int Game::screenHeight;
int Game::screenWidth;

void Game::init(const char *title, int xpos, int ypos, bool fullscreeen) {
  /*
  flags defines the state of the window either by the name or
  some number associated with the name.
  */
  int flags = 0;
  if (fullscreeen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  /*
  Now we initialize SDL. You can't call any SDL functions without initializing
  SDL first. When there's an error, SDL_Init returns -1.
  */
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialized...." << std::endl;

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
      std::cout << "SDL_GetDesktopDisplayMode failed: " << SDL_GetError()
                << std::endl;
    }

    screenWidth = dm.w;
    screenHeight = dm.h;

    window = SDL_CreateWindow(title, xpos, ypos, screenWidth / 2,
                              screenHeight / 2, flags);
    if (window) {
      std::cout << "Window created!" << std::endl;
    } else {
      std::cout << "Error: " << SDL_GetError()
                << std::endl; // SDL_GetError() specifies the error
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!" << std::endl;
    }

    isRunning = true;
  } else {
    isRunning = false;
    std::cout << "Error: " << SDL_GetError()
              << std::endl; // SDL_GetError() specifies the error
  }
  if (TTF_Init() < 0) {
    std::cout << "TTF_Init():" << TTF_GetError() << std::endl;
  }

  spaceship =
      new GameObject("Assets/Spaceship.png", 0, (screenHeight * 9) / 20,
                     (Game::screenHeight) / 20, (Game::screenHeight) / 20, 0);
  map = new Map();
  alien =
      new GameObject("Assets/test_alien_anim.png", 200, 200,
                     (Game::screenHeight) / 20, (Game::screenHeight) / 20, 1);
  int idle_alien = alien->createCycle(0, 32, 32, 2, 20);
  alien->setCurAnimation(idle_alien);
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event); // Waits indefinitely for the next available event.
  switch (event.type) {

  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    case SDLK_f:
      ToggleFullscreen(window);
      std::cout << "Switch" << std::endl;
      std::cout << "x: " << spaceship->getDestinationx() << std::endl;
      std::cout << "y: " << spaceship->getDestinationy() << std::endl;
      break;

    case SDLK_ESCAPE:
      // add pause menu
      isRunning = false;
      break;

    case SDLK_a:
      std::cout << "a down - move to the left" << std::endl;
      spaceship->moveLeft();
      break;

    case SDLK_d:
      std::cout << "d down - move to the right" << std::endl;
      spaceship->moveRight();
      break;

    case SDLK_SPACE:
      laser_beams.push_back(new GameObject(
          "Assets/laser_beam.png", spaceship->getDestinationx() + 20,
          spaceship->getDestinationy() - 8, 5, 8, 0));
      break;

    default:
      break;
    }
    break;

  case SDL_QUIT:
    isRunning = false;
    break;

  default:
    break;
  }
}

void Game::update() {
  // spaceship->Update();
  for (int i = 0; i < laser_beams.size(); i++) {
    if (laser_beams.at(i)->getDestinationx() >= screenWidth / 2 ||
        laser_beams.at(i)->getDestinationy() <= 0) {
      delete laser_beams.at(i);
      laser_beams.at(i) = NULL;
      laser_beams.erase(laser_beams.begin() + i);
      std::cout << laser_beams.size() << std::endl;
      std::cout << "laser beam out-of-bounds" << std::endl;
    } else {
      int x = laser_beams.at(i)->getDestinationx();
      int y = laser_beams.at(i)->getDestinationy();
      laser_beams.at(i)->setDestination(x, y - 20);
    }
  }
  if (alien)
    // alien->Update();
    alien->updateAnimation();
  for (int i = 0; i < laser_beams.size(); i++) {
    if (alien && collision(alien, laser_beams.at(i))) {
      std::cout << laser_beams.size() << std::endl;
      delete alien;
      alien = NULL;
      delete laser_beams.at(i);
      laser_beams.at(i) = NULL;
      laser_beams.erase(laser_beams.begin() + i);
      std::cout << "laser beam hit alien" << std::endl;
    }
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  // this is where you would add stuff to render
  map->LoadMap();
  TextureManager::Write("hello universe", 100, 100, 255, 0, 0, 255, 20);
  if (alien)
    alien->Render();
  if (spaceship)
    spaceship->Render();
  for (GameObject *laser : laser_beams) {
    laser->Render();
  }
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  if (spaceship)
    delete spaceship;
  if (alien)
    delete alien;
  delete map;
  for (GameObject *laser : laser_beams) {
    delete laser;
    laser = nullptr;
    std::cout << "cleaning laser" << std::endl;
  }
  laser_beams.clear();
  std::cout << "Game is cleaned" << std::endl;
}
