#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle(float xPos, float yPos)
{
	m_frect = {
		xPos - PADDLE::WIDTH / 2,
		yPos - PADDLE::HEIGTH / 2,
		PADDLE::WIDTH,
		PADDLE::HEIGTH
	};
	m_color = { 0, 0, 255 };
	m_velocity = { PADDLE::VELOCITY, PADDLE::VELOCITY };
	m_dir = { 0.0f, 0.0f };
}

Paddle::~Paddle()
{
}

void Paddle::setDirX(const float dirX)
{
	m_dir.x = dirX;
}

void Paddle::setDirY(const float dirY)
{
	m_dir.y = dirY;
}

void Paddle::move(const float xVel, const float yVel)
{
	m_frect.x += xVel * m_dir.x;
	m_frect.y += yVel * m_dir.y;
	
	// Check that the paddle does not go out of the screen
	if (right() > DISPLAY::WINDOW::WIDTH)
		m_frect.x = DISPLAY::WINDOW::WIDTH - PADDLE::WIDTH;
	else if (left() < 0)
		m_frect.x = 0;
	if (bottom() > DISPLAY::WINDOW::HEIGTH)
		m_frect.y = DISPLAY::WINDOW::HEIGTH - PADDLE::HEIGTH;
	else if (top() < 0)
		m_frect.y = 0;
}

void Paddle::update(const float& deltaTime)
{
	move(m_velocity.x * deltaTime, m_velocity.y * deltaTime);

}

void Paddle::render(SDL_Renderer& render)
{
	SDL_SetRenderDrawColor(&render, m_color.r, m_color.g, m_color.b, m_color.a);

	SDL_RenderFillRectF(&render, &m_frect);

	SDL_SetRenderDrawColor(&render, 0, 0, 0, 255);
}
