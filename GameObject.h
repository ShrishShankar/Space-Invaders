#ifndef GameObject_H
#define GameObject_H

#include "game.h"
#include <vector>

class GameObject {
public:
  GameObject(const char *textureSheet, int x, int y, bool isAnimated);
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

  int createCycle(int r, int w, int h, int totalFrames, int speed);
  void setCurAnimation(int c) {
    begin = 0;
    curAnim = c;
  }
  void updateAnimation();
  void reverse(bool r) { rev = r; }

private:
  int xpos;
  int ypos;
  bool isAnimated{0};

  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;

  // for animation
  struct cycle {
    int row;
    int w;
    int h;
    int totalFrames;
    int speed;
    int frame;
  };
  std::vector<cycle> animations;
  int curAnim;
  int begin;
  bool rev, nAb;
  int newAnim;
};

#endif // GameObject_H