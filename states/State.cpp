#include "stdafx.h"
#include "State.h"
#include "../MainGame.h"

State::State(MainGame& game) : m_pGame(&game)
{
	m_needPop = false;
	std::cout << "State Constructor" << "\n";
}

State::~State()
{
	m_pGame = nullptr;
	std::cout << "State Destructor" << "\n";
}

void State::needPop(bool status)
{
	m_needPop = status;
}

const bool& State::checkForQuit() const
{
	return (m_needPop);
}