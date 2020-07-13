#ifndef TextManager_H
#define TextManager_H
#include "game.h"

class TextureManager {
public:
  /**
   * Loads the texture to be applied on the renderer using the relative path to
   * the image file.
   * @param filename relative path to the image file.
   */
  static SDL_Texture *LoadTexture(const char *filename);

  /**
   * Renders the given texture on the screen.
   * @param texture texture created from image file using LoadTexture.
   * @param src the source rectangle
   * @param dest the destination rectangle
  */
  static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);

  /**
   * Writes text on the screen.
   * @param msg the string that needs to be rendered on the screen
   * @param x the x coordinate of the text
   * @param y the y coordinate of the text
   * @param r red value
   * @param b blue value
   * @param g green value
   * @param a alpha(transparency value)
   * @param size font size
  */
  static void Write(std::string msg, int x, int y, int r, int b, int g, int a,
                    int size);
};

#endif // TextManager_H
