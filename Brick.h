#ifndef BRICK_H
#define BRICK_H
#include "utility/FRectangle.h"

class Brick : public FRectangle
{
public:
	Brick(float xPos, float yPos);
	~Brick();

	bool isDestroyed() const;
	void destroy();
	void setDirX(const float dirX);
	void setDirY(const float dirY);
	void move(const float xVel, const float yVel);
	void update(const float& deltaTime);
	void render(SDL_Renderer& render);

private:
	bool m_destroyed{ false };
	SDL_Color m_color;

	SDL_FPoint m_velocity;
	SDL_FPoint m_dir;
};

#endif