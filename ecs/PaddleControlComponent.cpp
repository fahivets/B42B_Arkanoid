#include "stdafx.h"
#include "PaddleControlComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"

void PaddleControlComponent::init()
{
	m_pPhysComponent = &m_entity->getComponent<PhysicsComponent>();
}

void PaddleControlComponent::handleInput(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_RIGHT] && m_pPhysComponent->right() < DISPLAY::WINDOW::WIDTH)
	{
		//m_pPhysComponent->setDirX(1.0f);
		m_pPhysComponent->m_velocity.x = PADDLE::VELOCITY;
	}
	else if (keys[SDL_SCANCODE_LEFT] && m_pPhysComponent->left() > 0)
	{
		//m_pPhysComponent->setDirX(-1.0f);
		m_pPhysComponent->m_velocity.x = -PADDLE::VELOCITY;
	}
	else
	{
		//m_pPhysComponent->setDirX(0.0f);
		//m_pPhysComponent->setDirY(0.0f);
		m_pPhysComponent->m_velocity.x = 0;

	}

}