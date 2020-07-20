#ifndef UIBUTTONCOMPONENT_H
#define UIBUTTONCOMPONENT_H
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"

using TextureNameArray = std::array<const char*, 3>;
using ButtonTextureArray = std::array<SDL_Texture*, 3>;

struct UIButtonComponent : public Component
{
	enum ButtonState
	{
		NORMAL = 0,
		HOVER,
		PRESSED
	};

	// Constructor/Destructor
	UIButtonComponent(SDL_Renderer& rRenderer, TextureNameArray& buttonTextureArray);
	~UIButtonComponent() = default;

	// Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;

	void setFunction(std::function<void(void)> function);

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };

	SDL_FRect	m_dstFRect;
	ButtonTextureArray m_buttonTextureArray;
	ButtonState m_currentState{ ButtonState::NORMAL };
	std::function<void(void)> m_function = []() {};
};

#endif
