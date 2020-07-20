#include "stdafx.h"
#include"FontManager.h"

FontManager::FontManager(const std::string& folder, const std::string& extention)
	: m_folder("resource/" + folder + "/")
	, m_extention("." + extention)
{}

FontManager::~FontManager()
{
}

bool FontManager::isExists(const std::string& name) const
{
	return (m_fontMap.find(name) != m_fontMap.end());
}

void FontManager::set(const std::string& name, const int& fontSize)
{
	auto tmpPtr = loadFont(getFullFileName(name), fontSize);

	if (tmpPtr)
	{
		m_fontMap[name] = std::move(tmpPtr);
	}
	else if (!isExists("404_font"))
	{
		tmpPtr = loadFont(getFullFileName("404_font"), fontSize);
		if (!tmpPtr)
			assert("404_font <T_T> sempai");
		else
			m_fontMap[name] = std::move(tmpPtr);
	}
}

TTF_Font* FontManager::get(const std::string& name) const
{
	if (!isExists(name))
	{
		return (m_fontMap.at("404_font").get());
	}
	return m_fontMap.at(name).get();
}

void FontManager::init()
{
	if (TTF_Init() < 0)
	{
		std::cerr << "[SDL_ERROR] " << SDL_GetError() << std::endl;
	}
	set("404_font", 42);
}

SDLFontUPtr FontManager::loadFont(const std::string& path, const int& fontSize)
{
	auto* rawPtr = TTF_OpenFont(path.c_str(), fontSize);
	auto deleter = [](TTF_Font* font)
		{
			TTF_CloseFont(font);
		};

	return (SDLFontUPtr(rawPtr, deleter));
}

std::string FontManager::getFullFileName(const std::string& name)
{
	return (m_folder + name + m_extention);
}
