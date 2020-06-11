#ifndef Entity_H
#define Entity_H

#include "game.h"
#include "GameObject.h"
#include <vector>

class Entity : public GameObject {
public:
  Entity(const char *textureSheet, int x, int y)
      : GameObject(textureSheet, x, y) {
    rev = 0;
  }
  int createCycle(int r, int w, int h, int totalFrames, int speed);
  void setCurAnimation(int c) {
    begin = 0;
    curAnim = c;
  }
  void updateAnimation();
  void reverse(bool r) { rev = r; }

private:
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

#endif // Entity_H