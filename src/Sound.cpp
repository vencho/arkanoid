#include<Sound.h>

Mix_Music* Sound::music = NULL;
std::map<std::string, Mix_Chunk*> Sound::sounds = {};

void Sound::initSound() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(8);

    sounds.insert(std::pair<std::string, Mix_Chunk*>("start", Mix_LoadWAV("res/sound/start.wav")));
    sounds.insert(std::pair<std::string, Mix_Chunk*>("powerup", Mix_LoadWAV("res/sound/powerup.wav")));
    sounds.insert(std::pair<std::string, Mix_Chunk*>("tile", Mix_LoadWAV("res/sound/tile.wav")));
    sounds.insert(std::pair<std::string, Mix_Chunk*>("bounce", Mix_LoadWAV("res/sound/bounce.wav")));
    sounds.insert(std::pair<std::string, Mix_Chunk*>("enemy", Mix_LoadWAV("res/sound/enemy.wav")));
    sounds.insert(std::pair<std::string, Mix_Chunk*>("fire", Mix_LoadWAV("res/sound/fire.wav")));

    music = Mix_LoadMUS("res/music/music.wav");
}

void Sound::playMusic() {
    if (!(music == NULL)) {
        Mix_PlayMusic(music, -1);
    }
}

void Sound::free() {
    for(std::map<std::string, Mix_Chunk*>::iterator sound = sounds.begin(); sound != sounds.end(); ++sound) {
        Mix_FreeChunk(sound->second);
    }

    Mix_FreeMusic(music);
}

void Sound::playSound(std::string sound) {
    Mix_PlayChannel(-1, sounds.find(sound)->second, 0);
}
