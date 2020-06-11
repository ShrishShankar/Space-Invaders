#ifndef TextManager_H
#define TextManager_H
#include "game.h"

class TextureManager {
public:
  static SDL_Texture *LoadTexture(const char *filename);
  static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
  static void Write(const char *msg, int x, int y, int r, int b, int g, int a,
                    int size);
};

#endif // TextManager_H
