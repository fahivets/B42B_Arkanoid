#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H
#include "Component.h"
#include "BoxComponent.h"

struct RectangleComponent : public Component
{
	// Constructor/Destructor
	RectangleComponent(const SDL_Color &rColor);
	~RectangleComponent() = default;

	// Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;

	// Members
	BoxComponent* m_pBoxComp{ nullptr };
	SDL_Color m_color;
};

#endif