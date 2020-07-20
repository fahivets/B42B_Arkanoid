#include "stdafx.h"
#include "RectangleComponent.h"
#include "Entity.h"

// Constructor
RectangleComponent::RectangleComponent(const SDL_Color& rColor)
{
	m_color = rColor;
}

// Functions
void RectangleComponent::init()
{
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
}

void RectangleComponent::render(SDL_Renderer& rRender)
{
	SDL_SetRenderDrawColor(&rRender, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRectF(&rRender, &m_pBoxComp->m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}
