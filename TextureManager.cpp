#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename) {

  // SDL_Surface *tempSurface = IMG_Load(filename);
  // SDL_Texture *texture =
  //     SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  // SDL_FreeSurface(tempSurface);

  SDL_Texture *texture = SDL_CreateTexture(
      Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      Game::screenWidth / 2, Game::screenHeight / 2);

  texture = IMG_LoadTexture(Game::renderer, filename);

  return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::Write(std::string msg, int x, int y, int r, int b, int g,
                           int a, int size) {
  SDL_Surface *TextSurface;
  SDL_Texture *Texture;
  TTF_Font *font = TTF_OpenFont("Assets/open-sans/OpenSans-Italic.ttf", size);
  if (font == NULL) {
    std::cout << "TTF_OpenFont:" << TTF_GetError() << std::endl;
  }

  SDL_Color TextColor;
  // Setting text color
  TextColor.r = r;
  TextColor.b = b;
  TextColor.g = g;
  TextColor.a = a;

  const char *text = msg.c_str();

  TextSurface = TTF_RenderText_Solid(font, text, TextColor);

  SDL_Rect TextDest;
  // Setting the destination rectangle
  TextDest.x = x;
  TextDest.y = y;
  TextDest.w = TextSurface->w;
  TextDest.h = TextSurface->h;

  Texture = SDL_CreateTextureFromSurface(Game::renderer, TextSurface);
  SDL_FreeSurface(TextSurface);
  SDL_RenderCopy(Game::renderer, Texture, NULL, &TextDest);
  SDL_DestroyTexture(Texture);
  TTF_CloseFont(font);
}