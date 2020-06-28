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
	void handleInput(const Uint8* keys) override;

	// test
	void update(const float& deltaTime) {};
	void render(SDL_Renderer& rRender) {};



	// Members
	PhysicsComponent* m_pPhysComponent{ nullptr };
};

#endif