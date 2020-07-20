#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

using SDLTextureUPtr = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>;

class TextureManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	TextureManager() = delete;
	TextureManager(const std::string& folder, const std::string& extention);
	~TextureManager();

	// Functions
	bool isExists(const std::string& name) const;
	void set(SDL_Renderer& rRenderer, const std::string& name);
	SDL_Texture* get(const std::string& name) const;
	void init(SDL_Renderer& rRenderer);
	/*
	void setText();
	void getText();
	*/
private:
	// Private functions
	SDLTextureUPtr loadTexture(SDL_Renderer& rRenderer, const std::string& path);
	std::string getFullFileName(const std::string& name);

private:
//	bool m_status{ false };
	const std::string m_folder;
	const std::string m_extention;
	std::unordered_map<std::string, SDLTextureUPtr> m_textureMap;

	std::unordered_map<std::string, SDLTextureUPtr> m_textTextures;
	
};

#endif