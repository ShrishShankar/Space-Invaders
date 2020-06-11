#ifndef Audio_H
#define Audio_H

#include "game.h"

class Audio {
public:
  ~Audio();
  void load(const char *);
  void play();

private:
  SDL_AudioSpec waveSpec;
  Uint32 waveLength;
  Uint8 *waveBuffer;
  SDL_AudioDeviceID deviceID;
};

#endif // Audio_H