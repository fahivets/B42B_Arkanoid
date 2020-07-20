#include "stdafx.h"
#include "StartState.h"
#include "PlayingState.h"
#include "../MainGame.h"

StartState::StartState(MainGame& game) : State(game)
{
	std::cout << "Start State Constructor" << "\n";

	createButton({ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH / 2 }, { 42, 42 });
}

StartState::~StartState()
{
	std::cout << "Start State Destructor" << "\n";
}

void StartState::endState()
{
	std::cout << "Ending Start State" << "\n";
}
//old input
/*
void StartState::handleInput(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_Q])
	{
		needPop(true);
		std::cout << "Q = Quit" << " Pop status: " << checkForQuit() << "\n";
	}
	if (keys[SDL_SCANCODE_RETURN])
	{
		m_pGame->pushState<PlayingState>(*m_pGame);
		std::cout << "ENTER" << "\n";
	}
}
*/

void StartState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_Q))
	{
		needPop(true);
		std::cout << "Q = Quit" << " Pop status: " << checkForQuit() << "\n";
	}
	if (input.keyDown(SDL_SCANCODE_RETURN))
	{
		m_pGame->pushState<PlayingState>(*m_pGame);
		std::cout << "ENTER" << "\n";
	}

	m_entityManager.handleInput(input);
}

void StartState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);

}

void StartState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

// Entity factory
void StartState::createButton(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(Vector2f{ rSize.x, rSize.y });

	std::array<const char*, 3> buttonTexture{ "button_n", "button_h", "button_r" };
	entity.addComponent<UIButtonComponent>(m_pGame->getRenderer(), buttonTexture);
	// Set function
	auto& button(entity.getComponent<UIButtonComponent>());
	button.setFunction([]()
		{
			std::cout << "TEST CallBack function" << "\n";
		});

	entity.addGroup(ArkanoidGroup::GButton);
}
