#ifndef GameObject_H
#define GameObject_H

#include "game.h"
#include <vector>

class GameObject {
public:
  GameObject(const char *textureSheet, int x, int y, int w, int h,
             int lives = 1, bool isAnimated = false);
  ~GameObject() { std::cout << "GameObject is deleted" << std::endl; };

  /**
   * Renders the GameObject onto the screen, using the SDL_RenderCopy()
   * function.
   */
  void Render();

  /**
   * Sets the coordinates and dimensions of the source rectangle.
   */
  void setSource(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
  }
  int lives;

  /**
   * Returns the x coordinate of the GameObject.
   */
  int getDestinationx() { return destRect.x; }

  /**
   * Returns the x coordinate of the GameObject.
   */
  int getDestinationy() { return destRect.y; }

  /**
   * Sets the destination coordinates of the GameObject.
   */
  void setDestination(int x, int y) {
    destRect.x = x;
    destRect.y = y;
  }

  /**
   * Returns the width of the GameObject.
   */
  int getDestWidth() { return destRect.w; }

  /**
   * Returns the height of the GameObject.
   */
  int getDestHeight() { return destRect.h; }

  /**
   * Creates an animation cycle with information regarding the animation frames
   * from the source and adds it to 'animations' vector.
   * @param r the row no. in the image file.
   * @param w width of one frame in the specified row.
   * @param h height of one frame in the specified row.
   * @param totalFrames total no. of frames in the animation row.
   * @param speed speed of the animation.
   *
   * @return the index of the cycle in the 'animations' vector
   */
  int createCycle(int r, int w, int h, int totalFrames, int speed);

  /**
   * Sets the GameObject's current animation using the index of the cycle in the
   * 'animations' vector.
   * @param c Index of the specified animation cycle.
   */
  void setCurAnimation(int c) {
    begin = 0;
    curAnim = c;
  }

  /**
   * Sets and calculates the coordinates and dimensions of the source rectangle
   * to create the animation.
   */
  void updateAnimation();

  /**
   * Moves the GameObject to the right by p pixels.
   * @param p pixels
   */
  void moveRight(float p);

  /**
   * Moves the GameObject to the left by p pixels.
   * @param p pixels
   */
  void moveLeft(float p);

  /**
   * Moves the GameObject to the up by p pixels.
   * @param p pixels
   */
  void moveUp(float p);

  /**
   * Moves the GameObject to the down by p pixels.
   * @param p pixels
   */
  void moveDown(float p);

  /**
   * Checks if two GameObjects have collided.
   * @param a the bigger of the two GameObjects.
   * @param b the smaller of the two GameObjects.
   *
   * @returns 1 if collision has occured and 0 if not.
   */
  friend bool collision(GameObject *a, GameObject *b);

  /**
   * Deletes the elements of a vector of pointers to GameObjects.
   * @param vec vector of GameObjects
   * @param i index of the element to be deleted
   */
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