#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager(const std::string& folder)
	: m_folder(folder)
{}

TextureManager::~TextureManager()
{}

bool TextureManager::isExists(const std::string& name) const
{
	return (m_textureMap.find(name) != m_textureMap.end());
}


SDL_Texture* TextureManager::get(const std::string& name) const
{
	if (!isExists(name))
	{
		return (m_textureMap.at("fiasko.png").get());
	}
	return m_textureMap.at(name).get();
}

void TextureManager::set(SDL_Renderer& rRenderer, const std::string& name)
{
	if (isExists(name))
		return ;
	
	auto tmpPtr = loadTexture(rRenderer, getFullFileName(name));

	if (tmpPtr)
	{
		m_textureMap[name] = std::move(tmpPtr);
	}
	else if (!isExists("fiasko.png"))
	{
		tmpPtr = loadTexture(rRenderer, getFullFileName("fiasko.png"));
		if (!tmpPtr)
			assert("this is fiasko <T_T> sempai");
		else
			m_textureMap[name] = std::move(tmpPtr);
	}
}
// tmp functions for test
void TextureManager::init(SDL_Renderer& rRenderer)
{
	set(rRenderer, "fiasko.png");
}

// Private functions
SDLTextureUPtr TextureManager::loadTexture(SDL_Renderer& rRenderer, const std::string& path)
{
	auto* rawPtr = IMG_LoadTexture(&rRenderer, path.c_str());
	auto deleter = [](SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		};

	return (SDLTextureUPtr(rawPtr, deleter));
}

std::string TextureManager::getFullFileName(const std::string& name)
{
	return (m_folder + name);
}