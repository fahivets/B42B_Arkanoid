#include "stdafx.h"
#include "Brick.h"

Brick::Brick(float xPos, float yPos)
{
	m_frect = {
	xPos - BRICK::WIDTH / 2,
	yPos - BRICK::HEIGTH / 2,
	BRICK::WIDTH,
	BRICK::HEIGTH
	};
	m_color = { 255, 255, 0 };

	m_velocity = { BRICK::VELOCITY, BRICK::VELOCITY };
	m_dir = { 0.0f, 0.0f };
}

Brick::~Brick()
{
}

bool Brick::isDestroyed() const
{
	return (m_destroyed);
}

void Brick::destroy()
{
	m_destroyed = true;
}

void Brick::setDirX(const float dirX)
{
	m_dir.x = dirX;
}

void Brick::setDirY(const float dirY)
{
	m_dir.y = dirY;
}

void Brick::move(const float xVel, const float yVel)
{
}

void Brick::update(const float& deltaTime)
{
}

void Brick::render(SDL_Renderer& render)
{
	SDL_SetRenderDrawColor(&render, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRectF(&render, &m_frect);
	SDL_SetRenderDrawColor(&render, 0, 0, 0, 255);
}