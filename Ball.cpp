#include "stdafx.h"
#include "Ball.h"

Ball::Ball(float xPos, float yPos)
{
	m_frect = {
		xPos - BALL::RADIUS,
		yPos - BALL::RADIUS,
		BALL::RADIUS * 2,
		BALL::RADIUS * 2
	};
	m_color = {255, 0, 0};
	m_velocity = { BALL::VELOCITY, BALL::VELOCITY };
	m_dir = { -1, -1 };
}

Ball::~Ball()
{
}

void Ball::setDirX(const float dirX)
{
	m_dir.x = dirX;
}

void Ball::setDirY(const float dirY)
{
	m_dir.y = dirY;
}

void Ball::move(const float xVel, const float yVel)
{
	m_frect.x += xVel * m_dir.x;
	m_frect.y += yVel * m_dir.y;
}

void Ball::update(const float& deltaTime)
{
	move(m_velocity.x * deltaTime, m_velocity.y* deltaTime);

	if (left() < 0)
		setDirX(1.0f);
	else if (right() > DISPLAY::WINDOW::WIDTH)
		setDirX(-1.0f);
	if (top() < 0)
		setDirY(1.0f);
	else if (bottom() > DISPLAY::WINDOW::HEIGTH)
		setDirY(-1.0f);
}

void Ball::render(SDL_Renderer& render)
{
	SDL_SetRenderDrawColor(&render, m_color.r, m_color.g, m_color.b, m_color.a);

	SDL_RenderFillRectF(&render, &m_frect);

	SDL_SetRenderDrawColor(&render, 0, 0, 0, 255);
}

