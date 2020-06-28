#ifndef BALL_H
#define BALL_H

class Ball
{
public:
	Ball(float xPos, float yPos);
	~Ball();

	void setDirX(const float dirX);
	void setDirY(const float dirY);
	void move(const float xVel, const float yVel);
	void update(const float& deltaTime);
	void render(SDL_Renderer& render);

	float centerX() { return (m_frect.x + BALL::RADIUS); };
	float centerY() { return (m_frect.y + BALL::RADIUS); };
	float left() { return (centerX() - BALL::RADIUS); };
	float right() { return (centerX() + BALL::RADIUS); };
	float top() { return (centerY() - BALL::RADIUS); };
	float bottom() { return (centerY() + BALL::RADIUS); };
	
private:
	SDL_FRect m_frect;
	SDL_FPoint m_dir;
	SDL_FPoint m_velocity;
	SDL_Color m_color;
};

#endif