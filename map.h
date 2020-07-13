#ifndef Map_H
#define Map_H

#include "game.h"

class Map {
public:
  Map();
  ~Map() { std::cout << "Map is deleted" << std::endl; }
  
  /**
   * Loads the map's texture onto the screen.
  */
  void LoadMap();
  void DrawMap();

private:
  SDL_Rect src, dest;

  SDL_Texture *space;

  // int map[25][20];
};

#endif // Map_H