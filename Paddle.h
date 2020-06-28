#ifndef PADDLE_H
#define PADDLE_H
#include "utility/FRectangle.h"

class Paddle : public FRectangle
{
public:
	Paddle(float xPos, float yPos);
	~Paddle();

	void setDirX(const float dirX);
	void setDirY(const float dirY);
	void move(const float xVel, const float yVel);
	void update(const float& deltaTime);
	void render(SDL_Renderer& render);
	
private:
	SDL_FPoint m_dir;
	SDL_FPoint m_velocity;
	SDL_Color m_color;

};

#endif