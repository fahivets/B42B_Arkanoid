#ifndef PADDLECONTROLCOMPONENT_H
#define PADDLECONTROLCOMPONENT_H
#include "Component.h"

struct PhysicsComponent;

struct PaddleControlComponent : public Component
{
	// Constructor/Destructor
	PaddleControlComponent() = default;
	~PaddleControlComponent() = default;

	// Functions
	void init() override;
	//void handleInput(const Uint8* keys) override;
	void handleInput(const InputManager& input) override;

	// Members
	PhysicsComponent* m_pPhysComponent{ nullptr };
};

#endif