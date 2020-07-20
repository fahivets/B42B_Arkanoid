#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"

struct PhysicsComponent : public Component
{
	// Constructor/Destructor
	PhysicsComponent() = default;
	~PhysicsComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;

	BoxComponent& box() const;

	// Use a callback to handle the "out of bounds" event.
	std::function<void(const Vector2f&)> outOfBounds{ nullptr };
	
	// Members
	PositionComponent* m_pPosComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };
	Vector2f m_velocity;

};

#endif
