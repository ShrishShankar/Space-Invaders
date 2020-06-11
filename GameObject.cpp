#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y)
    : xpos{x}, ypos{y} {
  objTexture = TextureManager::LoadTexture(textureSheet);
  srcRect = 0;
  srcRect.y = 0;
  srcRect.w = 32;
  srcRect.h = 32;
  destRect.x = xpos;
  destRect.y = ypos;
  destRect.h = srcRect.h * 2;
  destRect.w = srcRect.w * 2;
}

void GameObject::Update() {}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
  // src decides how much of the image will be shown (basically crop).
  // dest decides what is size of the cropped image in the window and where will
  // it be placed.
}