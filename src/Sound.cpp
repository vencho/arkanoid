#include<Sound.h>

Mix_Music* Sound::music = NULL;

void Sound::initSound() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    music = Mix_LoadMUS("res/music/music.wav");
}

void Sound::playMusic() {
    if (!(music == NULL)) {
        Mix_PlayMusic(music, -1);
    }
}

void Sound::free() {
    Mix_FreeMusic(music);
}
