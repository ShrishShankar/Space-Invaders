#include "game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "map.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

GameObject *spaceship{nullptr};
GameObject *ufo{nullptr};
// std::vector<std::vector<GameObject *>> aliens(5, std::vector<GameObject
// *>(10));
GameObject *aliens[5][10];
std::vector<GameObject *> laser_beams;
std::vector<GameObject *> alien_beams;
Map *map{nullptr};

struct explosion {
  GameObject *strike;
  int frameCount;
};
std::vector<explosion> explosions;

int x_of_rightmost_alien = 0;
int x_of_leftmost_alien;
int y_of_bottommost_alien;

char left_or_right = 'r';
int isDown = 0;

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

    windowWidth = screenWidth / 1.5;
    windowHeight = screenHeight / 1.5;

    x_of_leftmost_alien = windowWidth;

    window =
        SDL_CreateWindow(title, xpos, ypos, windowWidth, windowHeight, flags);
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
      new GameObject("Assets/Spaceship.png", 0, (windowHeight * 37) / 40,
                     (windowHeight * 3) / 40, (windowHeight * 3) / 40, 0);
  map = new Map();
  ufo = new GameObject("Assets/ufo.png", 50, 50, windowHeight / 10,
                       (windowHeight * 3) / 40, 0);

  int k{0};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      aliens[i][j] =
          new GameObject("Assets/aliens.png", 2 * j * (windowHeight / 20),
                         100 + ((windowHeight / 20) * i), (windowHeight / 20),
                         (windowHeight / 20), 1);
      if (i == 0)
        k = 2;
      else if (i == 1 || i == 2)
        k = 0;
      else
        k = 1;
      int alien = aliens[i][j]->createCycle(k, 32, 32, 2, 20);
      aliens[i][j]->setCurAnimation(alien);
    }
  }
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event); // Waits indefinitely for the next available event.
  switch (event.type) {

  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    case SDLK_f:
      ToggleFullscreen(window);
      break;

    case SDLK_ESCAPE:
      // add pause menu
      isRunning = false;
      break;

    case SDLK_a:
      if (spaceship)
        spaceship->moveLeft(20);
      break;

    case SDLK_d:
      if (spaceship)
        spaceship->moveRight(20);
      break;

    default:
      break;
    }
    break;

  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_SPACE:
      if (spaceship) {
        laser_beams.push_back(
            new GameObject("Assets/laser_beam.png",
                           spaceship->getDestinationx() + windowHeight / 30,
                           spaceship->getDestinationy() - 8, 5, 8, 0));
      }
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
  for (int i = 0; i < laser_beams.size(); i++) {
    if (laser_beams.at(i)->getDestinationy() <= 0) {
      deleteVectorObjectPointers(&laser_beams, i);
      std::cout << "laser beam out-of-bounds" << std::endl;
    } else {
      int x = laser_beams.at(i)->getDestinationx();
      int y = laser_beams.at(i)->getDestinationy();
      laser_beams.at(i)->setDestination(x, y - 8);
    }
  }

  for (int i = 0; i < laser_beams.size(); i++) {
    if (ufo && collision(ufo, laser_beams.at(i))) {
      std::cout << laser_beams.size() << std::endl;
      explosions.push_back(
          {new GameObject("Assets/collision.png", ufo->getDestinationx(),
                          ufo->getDestinationy(), ufo->getDestWidth(),
                          ufo->getDestHeight(), 0),
           0});
      delete ufo;
      ufo = nullptr;
      deleteVectorObjectPointers(&laser_beams, i);
      std::cout << "laser beam hit alien" << std::endl;
    }
  }

  int count = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (aliens[i][j]) {
        aliens[i][j]->updateAnimation();
        if (count == 0) {
          x_of_leftmost_alien = aliens[i][j]->getDestinationx();
          y_of_bottommost_alien = aliens[i][j]->getDestinationy();
          x_of_rightmost_alien = 0;
          count++;
        }
        if (x_of_rightmost_alien < aliens[i][j]->getDestinationx())
          x_of_rightmost_alien = aliens[i][j]->getDestinationx();
        if (x_of_leftmost_alien > aliens[i][j]->getDestinationx())
          x_of_leftmost_alien = aliens[i][j]->getDestinationx();
        if (y_of_bottommost_alien < aliens[i][j]->getDestinationy())
          y_of_bottommost_alien = aliens[i][j]->getDestinationy();
      }
    }
  }

  for (int i = laser_beams.size() - 1; i >= 0; i--) {
    if (laser_beams[i]->getDestinationy() <=
        y_of_bottommost_alien + (windowHeight / 20)) {
      std::cout << "laser y: " << laser_beams[i]->getDestinationy()
                << "\ny_of_bottommost_alien: "
                << y_of_bottommost_alien + (windowHeight / 20) << std::endl;
      for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
          if (aliens[row][col] && laser_beams[i] &&
              collision(aliens[row][col], laser_beams[i])) {
            explosions.push_back(
                {new GameObject("Assets/collision.png",
                                aliens[row][col]->getDestinationx(),
                                aliens[row][col]->getDestinationy(),
                                aliens[row][col]->getDestWidth(),
                                aliens[row][col]->getDestHeight(), 0),
                 0});
            delete aliens[row][col];
            aliens[row][col] = nullptr;
            deleteVectorObjectPointers(&laser_beams, i);
          }
        }
      }
    }
  }

  int r1 = -1;
  int c1 = 11;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (aliens[i][j]) {
        if (spaceship &&
            aliens[i][j]->getDestinationx() > spaceship->getDestinationx() &&
            aliens[i][j]->getDestinationx() + aliens[i][j]->getDestWidth() <
                spaceship->getDestinationx() + spaceship->getDestWidth()) {
          c1 = j;
        }
        if (isDown == 1) {
          aliens[i][j]->moveDown(10);
        } else {
          if (left_or_right == 'r') {
            if (x_of_rightmost_alien + 1 >=
                Game::screenWidth / 1.5 - aliens[i][j]->getDestWidth()) {
              left_or_right = 'l';
              aliens[i][j]->moveDown(10);
              isDown = 1;
            } else
              aliens[i][j]->moveRight(1);
          } else if (left_or_right == 'l') {
            if (x_of_leftmost_alien - 1 <= 0) {
              left_or_right = 'r';
              aliens[i][j]->moveDown(10);
              isDown = 1;
            } else
              aliens[i][j]->moveLeft(1);
          }
        }
      }
    }
  }
  isDown = 0;
  if (frameCount % 50 == 0) {
    int c = (rand() % 10) + 1;
    int r = 4;
    for (int i = 4; i >= 0; i--) {
      if (aliens[i][c]) {
        r = i;
        break;
      }
    }

    if (aliens[r][c]) {
      alien_beams.push_back(new GameObject(
          "Assets/laser_beam.png",
          aliens[r][c]->getDestinationx() +
              (aliens[r][c]->getDestWidth() - 4) / 2,
          aliens[r][c]->getDestinationy() + aliens[r][c]->getDestHeight() + 8,
          4, 8, 0));
    }
  }

  if (frameCount % 25 == 0) {
    for (int i = 4; i >= 0; i--) {
      if (aliens[i][c1]) {
        r1 = i;
        break;
      }
    }

    if (aliens[r1][c1] && c1 < 11) {

      alien_beams.push_back(
          new GameObject("Assets/laser_beam.png",
                         aliens[r1][c1]->getDestinationx() +
                             (aliens[r1][c1]->getDestWidth() - 4) / 2,
                         aliens[r1][c1]->getDestinationy() +
                             aliens[r1][c1]->getDestHeight() + 8,
                         4, 8, 0));
    }
  }
  for (int i = 0; i < alien_beams.size(); i++) {
    if (alien_beams.at(i)->getDestinationy() >= windowHeight) {
      deleteVectorObjectPointers(&alien_beams, i);
      std::cout << "alien beam out-of-bounds" << std::endl;
    } else {
      int x = alien_beams.at(i)->getDestinationx();
      int y = alien_beams.at(i)->getDestinationy();
      alien_beams.at(i)->setDestination(x, y + 5);
    }
  }

  for (int i = 0; i < alien_beams.size(); i++) {
    if (spaceship && collision(spaceship, alien_beams.at(i))) {
      std::cout << alien_beams.size() << std::endl;
      explosions.push_back(
          {new GameObject("Assets/collision.png", spaceship->getDestinationx(),
                          spaceship->getDestinationy(),
                          spaceship->getDestWidth(), spaceship->getDestHeight(),
                          0),
           0});
      delete spaceship;
      spaceship = nullptr;
      deleteVectorObjectPointers(&alien_beams, i);
      std::cout << "laser beam hit spaceship" << std::endl;
    }
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  // this is where you would add stuff to render
  map->LoadMap();
  TextureManager::Write("Score: 0", 0, 0, 255, 0, 0, 255, 20);
  if (ufo)
    ufo->Render();
  if (spaceship)
    spaceship->Render();
  for (GameObject *laser : laser_beams) {
    laser->Render();
  }

  for (GameObject *aliens_beam : alien_beams) {
    aliens_beam->Render();
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (aliens[i][j])
        aliens[i][j]->Render();
    }
  }

  for (int i = 0; i < explosions.size(); i++) {
    if (explosions[i].frameCount < 10) {
      explosions[i].strike->Render();
      explosions[i].frameCount += 1;
    } else {
      delete explosions[i].strike;
      explosions[i].strike = nullptr;
      explosions.erase(explosions.begin() + i);
    }
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
  if (ufo)
    delete ufo;
  delete map;
  for (GameObject *laser : laser_beams) {
    delete laser;
    laser = nullptr;
    std::cout << "cleaning laser" << std::endl;
  }
  laser_beams.clear();
  std::cout << "Game is cleaned" << std::endl;
}
