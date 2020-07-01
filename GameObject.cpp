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
  destRect.h = (Game::screenHeight) / 20;
  destRect.w = (Game::screenHeight) / 20;
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

void GameObject::moveRight() {
  if (destRect.x + Game::screenHeight/60 <= Game::screenWidth/2 - Game::screenHeight/20)
    destRect.x = destRect.x + 16;
}

void GameObject::moveLeft() {
  if (destRect.x - Game::screenHeight/60 >= 0)
    destRect.x = destRect.x - 16;
}
void GameObject::moveUp() {
  if (destRect.y + Game::screenHeight/60 <= Game::screenHeight/2)
    destRect.y = destRect.y + 64;
}
void GameObject::moveDown() {
  if (destRect.y - Game::screenHeight/60 >= 0)
    destRect.y = destRect.y - 64;
}