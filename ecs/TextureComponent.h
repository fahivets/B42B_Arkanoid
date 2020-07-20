#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"

/*
	TODO: 
		- do i need here PosComp? srcRect/dstRect?

*/

struct TextureComponent : public Component
{
	TextureComponent(SDL_Renderer& rRenderer, const char* textureName);
	~TextureComponent() = default;

	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };

	std::string	m_textureName;
	SDL_Texture* m_texture{ nullptr };
	//SDL_Rect	m_srcRect;
	SDL_FRect	m_dstFRect;
};

#endif