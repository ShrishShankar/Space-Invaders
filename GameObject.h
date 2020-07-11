#ifndef GameObject_H
#define GameObject_H

#include "game.h"
#include <vector>

class GameObject {
public:
  GameObject(const char *textureSheet, int x, int y, int w, int h,
             bool isAnimated);
  ~GameObject() { std::cout << "GameObject is deleted" << std::endl; };

  void Update();
  void Render();

  void setSource(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
  }

  int getDestinationx() { return destRect.x; }

  int getDestinationy() { return destRect.y; }

  void setShots(int shots) { shots = shots; }

  void setDestination(int x, int y) {
    destRect.x = x;
    destRect.y = y;
  }

  int getDestWidth() { return destRect.w; }
  int getDestHeight() { return destRect.h; }

  int createCycle(int r, int w, int h, int totalFrames, int speed);
  void setCurAnimation(int c) {
    begin = 0;
    curAnim = c;
  }
  void updateAnimation();
  void moveRight(float p);
  void moveLeft(float p);
  void moveUp(float p);
  void moveDown(float p);

  friend bool collision(GameObject *a, GameObject *b);
  friend void deleteVectorObjectPointers(std::vector<GameObject *> *vec, int i);

private:
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
};

#endif // GameObject_H