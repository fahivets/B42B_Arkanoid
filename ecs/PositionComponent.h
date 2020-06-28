#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H
#include "Component.h"

struct PositionComponent : public Component
{
	// Constructor/Destructor
	PositionComponent(const Vector2f& rPosition = { 0.0f, 0.0f });
//	PositionComponent(float xPos, float yPos);
	~PositionComponent() = default;

	// Functions
	float x() const noexcept;
	float y() const noexcept;
	
	// test
	void init() {};
	void update(const float& deltaTime) {};
	void render(SDL_Renderer& rRender) {};
	void handleInput(const Uint8* keys) {};

	// Members
	Vector2f m_position;
};
#endif
