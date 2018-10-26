#ifndef SOUND_H_DEFINED
#define SOUND_H_DEFINED

#include<SDL_mixer.h>

class Sound {
    public:
        static Mix_Music* music;

        static void initSound();
        static void playMusic();
        static void free();
};

#endif
