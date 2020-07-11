#include "map.h"
#include "TextureManager.h"
#include <vector>

std::vector<std::vector<int>> bg(Game::screenWidth,
                                 std::vector<int>(Game::screenHeight, 0));

Map::Map() {
  space = TextureManager::LoadTexture("Assets/space.png");
  src.x = src.y = 0;
  src.h = dest.h = 32;
  src.w = dest.w = 32;

  dest.x = dest.y = 0;
}

void Map::LoadMap() {
  for (int row = 0; row < Game::screenHeight / 32; row++) {
    for (int column = 0; column < Game::screenWidth / 32; column++) {
      // arr[row][column] = bg[row][column];
      dest.x = column * 32;
      dest.y = row * 32;
      TextureManager::Draw(space, src, dest);
    }
  }
}

void Map::DrawMap() {}
