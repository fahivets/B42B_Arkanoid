#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "Component.h"
#include "PositionComponent.h"

struct PhysicsComponent : public Component
{
	// Constructor/Destructor
	PhysicsComponent(const Vector2f& rSize);
	~PhysicsComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;

	void setDirX(const float dirX);
	void setDirY(const float dirY);
	float x() const noexcept;
	float y() const noexcept;
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;

	//Test
	// Use a callback to handle the "out of bounds" event.
	std::function<void(const Vector2f&)> outOfBounds;
	// test
	void render(SDL_Renderer& rRender) {};
	void handleInput(const Uint8* keys) {};

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	Vector2f m_velocity;
	Vector2f m_dir;
	Vector2f m_size;
};

#endif
