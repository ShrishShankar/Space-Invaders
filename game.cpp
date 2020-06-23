#include "game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "map.h"
#include <iostream>

GameObject *spaceship;
GameObject *alien;
Map *map;

Game::Game() {}
Game::~Game() {}

SDL_Renderer *Game::renderer = nullptr;

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreeen) {
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

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
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

  spaceship = new GameObject("Assets/Spaceship.png", 0, 0, 0);
  map = new Map();
  alien = new GameObject("Assets/test_alien_anim.png", 100, 100, 1);
  int idle_alien = alien->createCycle(0, 32, 32, 2, 10);
  alien->setCurAnimation(idle_alien);
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event); // Waits indefinitely for the next available event.
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() {
  // spaceship->Update();
  alien->updateAnimation();
  // alien->Update();
}

void Game::render() {
  SDL_RenderClear(renderer);
  // this is where you would add stuff to render
  map->LoadMap();
  TextureManager::Write("hello universe", 100, 100, 255, 0, 0, 255, 20);
  alien->Render();
  spaceship->Render();
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game is cleaned" << std::endl;
}
