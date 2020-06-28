#include "stdafx.h"
#include "RectangleComponent.h"
#include "Entity.h"

// Constructor
RectangleComponent::RectangleComponent(const Vector2f& rSize, const SDL_Color& rColor)
{
	m_fRect.w = rSize.x;
	m_fRect.h = rSize.y;
	m_color = rColor;
}

// Functions
void RectangleComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}

void RectangleComponent::update(const float& deltaTime)
{
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}

void RectangleComponent::render(SDL_Renderer& rRender)
{
	SDL_SetRenderDrawColor(&rRender, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRectF(&rRender, &m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}
