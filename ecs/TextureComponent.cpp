#include"stdafx.h"
#include "TextureComponent.h"
#include "Entity.h"

TextureComponent::TextureComponent(SDL_Renderer& rRenderer, const char* textureName)
{
	m_textureName = textureName;
	ResourceHolder::get().textures.set(rRenderer, m_textureName);
	m_texture = ResourceHolder::get().textures.get(m_textureName);
}

void TextureComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();

	/*
	m_srcRect = {
	0,
	0,
	static_cast<int>(m_pPhysComp->m_size.x),
	static_cast<int>(m_pPhysComp->m_size.y)
	};
	*/
	m_dstFRect = {
		m_pBoxComp->x(),
		m_pBoxComp->y(),
		m_pBoxComp->w(),
		m_pBoxComp->h(),
	};
}

void TextureComponent::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_texture, 0, &m_dstFRect);
}

void TextureComponent::update(const float& deltaTime)
{
	/*
	m_srcRect = {
	0,
	0,
	static_cast<int>(m_pPhysComp->m_size.x),
	static_cast<int>(m_pPhysComp->m_size.y)
	};
	*/
	m_dstFRect = {
		m_pBoxComp->x(),
		m_pBoxComp->y(),
		m_pBoxComp->w(),
		m_pBoxComp->h(),
	};
}
