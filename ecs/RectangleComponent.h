#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H
#include "Component.h"
#include "PositionComponent.h"

struct RectangleComponent : public Component
{
	// Constructor/Destructor
	RectangleComponent(const Vector2f& rSize, const SDL_Color &rColor);
	~RectangleComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;

	// test
	void handleInput(const Uint8* keys) {};

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	SDL_FRect m_fRect;
	SDL_Color m_color;
};

#endif