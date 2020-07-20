#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager(const std::string& folder, const std::string& extention)
	: m_folder("resource/" + folder + "/")
	, m_extention("." + extention)
{}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

bool AudioManager::isSoundExists(const std::string& name) const
{
	return (m_soundMap.find(name) != m_soundMap.end());
}

bool AudioManager::isMusicExists(const std::string& name) const
{
	return (m_musicMap.find(name) != m_musicMap.end());
}

void AudioManager::setSound(const std::string& name)
{
	auto tmpPtr = loadSound(getFullFileName(name));

	if (tmpPtr)
	{
		m_soundMap[name] = std::move(tmpPtr);
	}
	else if (!isSoundExists("404_sound"))
	{
		tmpPtr = loadSound(getFullFileName("404_sound"));
		if (!tmpPtr)
			assert("404_sound <T_T> sempai");
		else
			m_soundMap[name] = std::move(tmpPtr);
	}
}

void AudioManager::setMusic(const std::string& name)
{
	auto tmpPtr = loadMusic(getFullFileName(name));

	if (tmpPtr)
	{
		m_musicMap[name] = std::move(tmpPtr);
	}
	else if (!isMusicExists("404_music"))
	{
		tmpPtr = loadMusic(getFullFileName("404_music"));
		if (!tmpPtr)
			assert("404_msuci <T_T> sempai");
		else
			m_musicMap[name] = std::move(tmpPtr);
	}
}

Mix_Chunk* AudioManager::getSound(const std::string& name) const
{
	if (!isSoundExists(name))
	{
		return (m_soundMap.at("404_sound").get());
	}
	return m_soundMap.at(name).get();
}

Mix_Music* AudioManager::getMusic(const std::string& name) const
{
	if (!isMusicExists(name))
	{
		return (m_musicMap.at("404_music").get());
	}
	return m_musicMap.at(name).get();
}

void AudioManager::playSound(const std::string& name, const int& loops, const int& channel, const int& volume) const
{
	/*
		Play sound effect file
		@param name -		sound effect name in sound map;

		@param loops -		if loops == -1, loop forever,
							otherwise play it loops + 1 times,
							default = 0;

		@param channel -	channel to play on,
							or -1 for the first free unreserved channel, default = -1;
	*/

	Mix_Volume(channel, volume);
	if (Mix_PlayChannel(channel, getSound(name), loops) == -1)
	{	
		std::cerr << "[MIX_PLAYCHANNEL_ERROR] " << Mix_GetError() << std::endl;
	}
}

void AudioManager::playMusic(const std::string& name, const int& loops, const int& volume) const
{
	/*
		Play music file
		@param name -	sound effect name in sound map;

		@param loops -	if loops == -1, loop forever,
						otherwise play it loops times,
						default = -1;
	*/
	Mix_VolumeMusic(volume);
	if (Mix_PlayMusic(getMusic(name), loops) == -1)
	{	
		std::cerr << "[MIX_PLAYMUSIC_ERROR] " << Mix_GetError() << std::endl;
	}
}

void AudioManager::pauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::stopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::resumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::setSoundVolume(const int& channel, const int& volume)
{
	Mix_Volume(channel, volume);
}

void AudioManager::setMusicVolume(const int& volume)
{
	Mix_VolumeMusic(volume);
}

void AudioManager::init()
{
	/*
		Parameter can be a bitwise combination of:
		MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
	*/
	int flags = MIX_INIT_FLAC | MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if ((initted&flags) != flags)
	{	
		std::cerr << "[MIX_ERROR] " << Mix_GetError() << std::endl;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cerr << "[MIX_AUDIO_ERROR] " << Mix_GetError() << std::endl;
	}
	setSound("404_sound");
	setMusic("404_music");
}

SDLChunkUPtr AudioManager::loadSound(const std::string& path)
{
	auto* rawPtr = Mix_LoadWAV(path.c_str());
	auto deleter = [](Mix_Chunk* chunk)
	{
		Mix_FreeChunk(chunk);
	};

	return (SDLChunkUPtr(rawPtr, deleter));
}

SDLMusicUPtr AudioManager::loadMusic(const std::string& path)
{
	auto* rawPtr = Mix_LoadMUS(path.c_str());
	auto deleter = [](Mix_Music* music)
	{
		Mix_FreeMusic(music);
	};

	return (SDLMusicUPtr(rawPtr, deleter));
}

std::string AudioManager::getFullFileName(const std::string& name)
{
	return (m_folder + name + m_extention);
}
