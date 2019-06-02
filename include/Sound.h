#ifndef SOUND_H_DEFINED
#define SOUND_H_DEFINED

#include<map>
#include<string>
#include<SDL_mixer.h>

class Sound {
    public:
        static Mix_Music* music;
        static std::map<std::string, Mix_Chunk*> sounds;

        static void initSound();
        static void playMusic();
        static void playSound(std::string sound);
        static void free();
};

#endif
