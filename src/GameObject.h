#ifndef GameObject_H
#define GameObject_H

#include "game.h"

class GameObject {
public:
  GameObject(const char *textureSheet, int x, int y);
  ~GameObject();

  void Update();
  void Render();

  void setSource(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
  }

  void setDestination(int x, int y, int w, int h) {
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
  }

private:
  int xpos;
  int ypos;

  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};

#endif // GameObject_H