#include "stdafx.h"
#include "StartState.h"
#include "PlayingState.h"
#include "../MainGame.h"

StartState::StartState(MainGame& game) : State(game)
{
	std::cout << "Start State Constructor" << "\n";
}

StartState::~StartState()
{
	std::cout << "Start State Destructor" << "\n";
}

void StartState::endState()
{
	std::cout << "Ending Start State" << "\n";
}

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

void StartState::update(const float& deltaTime)
{

}

void StartState::render(SDL_Renderer& render)
{

}