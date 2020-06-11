#include "Entity.h"

int Entity::createCycle(int r, int w, int h, int totalFrames, int speed) {
  cycle tmp;
  tmp.row = r - 1;
  tmp.w = w;
  tmp.h = h;
  tmp.totalFrames = totalFrames;
  tmp.speed = speed;
  tmp.frame = 0;
  animations.push_back(tmp);
  return animations.size() - 1;
}

void Entity::updateAnimation() {
  setSource(animations[curAnim].w * animations[curAnim].frame,
            animations[curAnim].row * animations[curAnim].h,
            animations[curAnim].w, animations[curAnim].h);

  if (begin > animations[curAnim].speed) {
    if (!rev)
      animations[curAnim].frame++;
    if (rev)
      animations[curAnim].frame--;
    begin = 0;
  }
  begin++;
  if (animations[curAnim].frame >= animations[curAnim].totalFrames) {
    animations[curAnim].frame = 0;
  }
}