#ifndef LABLECOMPONENT_H
#define LABLECOMPONENT_H
#include "Component.h"
#include "BoxComponent.h"

struct LableComponent : public Component
{
	// Constructor/Destructor
	LableComponent();
	~LableComponent();

	// Functions
	void init() override;

	// Members
	BoxComponent* m_pBoxComp{ nullptr };
	SDL_Texture* m_textTexture{ nullptr };
	TTF_Font* m_lablefont;
};

#endif

