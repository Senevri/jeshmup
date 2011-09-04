#include <iostream>
#include "Zounds.h"

using namespace std;	

Zounds::Zounds(){
	m_rate = 44100;
	m_buffer = 4096;
	m_channels = 2;
	m_format = AUDIO_S16SYS;
	m_songs = NULL; m_sound = NULL;
	if(Mix_OpenAudio(m_rate, m_format, m_channels, m_buffer) != 0) { 
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError()); 
		exit(1); 
	}
	Mix_QuerySpec(&m_rate, &m_format, &m_channels);
}
Zounds::~Zounds(){
	Mix_FreeChunk(m_sound);
	Mix_CloseAudio();
}

void cbtest() {
	//Zounds::musicDone();
}

void Zounds::playMusic(std::string filename, int loops){
	if (m_songs == NULL) {
		cout << "playMusic:" << filename  <<endl;
		m_songs = Mix_LoadMUS(filename.c_str());
		cout << m_songs <<endl;
		Mix_PlayMusic(m_songs, loops);
		Mix_HookMusicFinished((void (*)())&Zounds::musicDone);
	//	Mix_HookMusicFinished(cbtest);
	} else {
		musicDone();
		m_songs = NULL;
		playMusic(filename, loops);
	}
}
int Zounds::playSound(std::string filename, int loops){
	if (NULL == m_sound) {
		m_sound = Mix_LoadWAV(filename.c_str());
		return Mix_PlayChannel(-1, m_sound, loops);
	} else {
		return Mix_PlayChannel(-1, m_sound, loops);		
	} 
}

void Zounds::musicDone(){
	cout << "musicDone" <<endl;
	Mix_HaltMusic();
	Mix_FreeMusic(m_songs);
}
