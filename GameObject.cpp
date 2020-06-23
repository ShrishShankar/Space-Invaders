#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y, bool isAnimated)
    : xpos{x}, ypos{y} {
  objTexture = TextureManager::LoadTexture(textureSheet);
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = 32;
  srcRect.h = 32;
  destRect.x = xpos;
  destRect.y = ypos;
  destRect.h = srcRect.h * 2;
  destRect.w = srcRect.w * 2;
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