#include "stdafx.h"
#include "PhysicsComponent.h"
#include "Entity.h"

void PhysicsComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
}

void PhysicsComponent::update(const float& deltaTime)
{
	m_pPosComp->m_position += m_velocity * deltaTime;

	if (outOfBounds == nullptr)
		return;

	if (m_pBoxComp->left() < 0)
	{
		outOfBounds(Vector2f{ 1.f, 0.f });
	}
	else if (m_pBoxComp->right() > DISPLAY::WINDOW::WIDTH)
	{
		outOfBounds(Vector2f{ -1.f, 0.f });
	}
	if (m_pBoxComp->top() < 0)
	{
		outOfBounds(Vector2f{ 0.f, 1.f });
	}
	else if (m_pBoxComp->bottom() > DISPLAY::WINDOW::HEIGTH)
	{
		outOfBounds(Vector2f{ 0.f, -1.f });
	}
}

BoxComponent& PhysicsComponent::box() const
{
	return (*m_pBoxComp);
}