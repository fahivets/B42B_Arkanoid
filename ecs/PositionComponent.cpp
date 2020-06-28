#include "stdafx.h"
#include "PositionComponent.h"
#include "utility/Vector2f.h"

PositionComponent::PositionComponent(const Vector2f& rPosition) : m_position(rPosition)
{
}
/*
PositionComponent::PositionComponent(float rXPos, float rYPos)
{
	m_position.x = rXPos;
	m_position.y = rYPos;
}
*/
float PositionComponent::x() const noexcept
{
	return (m_position.x);
}

float PositionComponent::y() const noexcept
{
	return (m_position.y);
}
