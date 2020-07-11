#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y, int w, int h,
                       bool isAnimated) {
  objTexture = TextureManager::LoadTexture(textureSheet);
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = 32;
  srcRect.h = 32;
  destRect.x = x;
  destRect.y = y;
  destRect.h = h;
  destRect.w = w;
  // src decides how much of the image will be shown (basically crop).
  // dest decides what is size of the cropped image in the window and where will
  // it be placed.
}

void GameObject::Update() {}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

int GameObject::createCycle(int r, int w, int h, int totalFrames, int speed) {
  cycle tmp;
  tmp.row = r;
  tmp.w = w;
  tmp.h = h;
  tmp.totalFrames = totalFrames;
  tmp.speed = speed;
  tmp.frame = 0;
  animations.push_back(tmp);
  return animations.size() - 1;
}

void GameObject::updateAnimation() {
  setSource(animations[curAnim].w * animations[curAnim].frame,
            animations[curAnim].row * animations[curAnim].h,
            animations[curAnim].w, animations[curAnim].h);

  if (begin > animations[curAnim].speed) {
    animations[curAnim].frame++;
    begin = 0;
  }
  begin++;
  if (animations[curAnim].frame >= animations[curAnim].totalFrames) {
    animations[curAnim].frame = 0;
  }
}

void GameObject::moveRight(float p) {
  if (destRect.x + p <= Game::screenWidth / 1.5 - destRect.w)
    destRect.x = destRect.x + p;
}

void GameObject::moveLeft(float p) {
  if (destRect.x - p >= 0)
    destRect.x = destRect.x - p;
}
void GameObject::moveUp(float p) {
  if (destRect.y - p >= 0)
    destRect.y = destRect.y - p;
}
void GameObject::moveDown(float p) {
  if (destRect.y + p <= Game::screenHeight / 1.5 - destRect.h)
    destRect.y = destRect.y + p;
}

bool collision(GameObject *a, GameObject *b) {
  int left_a = a->destRect.x;
  int right_a = left_a + a->destRect.w;
  int top_a = a->destRect.y;
  int bottom_a = top_a + a->destRect.h;

  int left_b = b->destRect.x;
  int right_b = left_b + b->destRect.w;
  int top_b = b->destRect.y;
  int bottom_b = top_b + b->destRect.h;

  if (((left_a < left_b && left_b < right_a) ||
       (left_a < right_b && right_b < right_a)) &&
      ((top_a < top_b && top_b < bottom_a) ||
       (top_a < bottom_b && bottom_b < bottom_a)))

    return true;

  else {
    return false;
  }
}

void deleteVectorObjectPointers(std::vector<GameObject *> *vec, int i) {
  delete vec->at(i);
  vec->at(i) = nullptr;
  vec->erase(vec->begin() + i);
}