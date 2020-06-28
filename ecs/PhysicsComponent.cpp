#include "stdafx.h"
#include "PhysicsComponent.h"
#include "Component.h"
#include "Entity.h"

PhysicsComponent::PhysicsComponent(const Vector2f& rSize) : m_size(rSize)
{
}

void PhysicsComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
}

void PhysicsComponent::update(const float& deltaTime)
{
	/*
	auto& val = m_dir * deltaTime;
	val *= m_velocity;
	m_pPosComp->m_position += val;
	*/
	m_pPosComp->m_position += m_velocity * deltaTime;

	if (outOfBounds == nullptr) return;

	if (left() < 0)
		outOfBounds(Vector2f{ 1.f, 0.f });
	else if (right() > DISPLAY::WINDOW::WIDTH)
		outOfBounds(Vector2f{ -1.f, 0.f });

	if (top() < 0)
		outOfBounds(Vector2f{ 0.f, 1.f });
	else if (bottom() > DISPLAY::WINDOW::HEIGTH)
		outOfBounds(Vector2f{ 0.f, -1.f });

	/*
	if (left() < 0)
		setDirX(1.0f);
	else if (right() > DISPLAY::WINDOW::WIDTH)
		setDirX(-1.0f);

	if (top() < 0)
		setDirY(1.0f);
	else if (bottom() > DISPLAY::WINDOW::HEIGTH)
		setDirY(-1.0f);

	*/
}

void PhysicsComponent::setDirX(const float dirX)
{
	m_dir.x = dirX;
}

void PhysicsComponent::setDirY(const float dirY)
{
	m_dir.y = dirY;
}

float PhysicsComponent::x() const noexcept
{
	return (m_pPosComp->x());
}

float PhysicsComponent::y() const noexcept
{
	return (m_pPosComp->y());
}

float PhysicsComponent::left() const noexcept
{
	return (x() - (m_size.x / 2));
}

float PhysicsComponent::right() const noexcept
{
	return (x() + (m_size.x / 2));
}

float PhysicsComponent::top() const noexcept
{
	return (y() - (m_size.y / 2));
}

float PhysicsComponent::bottom() const noexcept
{
	return (y() + (m_size.y / 2));
}
