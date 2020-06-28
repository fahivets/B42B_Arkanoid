#include "stdafx.h"
#include "FRectangle.h"

float FRectangle::centerX() const noexcept
{
	return (m_frect.x + (m_frect.w / 2));
}

float FRectangle::centerY() const noexcept
{
	return (m_frect.y + (m_frect.h / 2));
}

float FRectangle::left() const noexcept
{
	return (centerX() - (m_frect.w / 2));
}

float FRectangle::right() const noexcept
{
	return (centerX() + (m_frect.w / 2));
}

float FRectangle::top() const noexcept
{
	return (centerY() - (m_frect.h / 2));
}

float FRectangle::bottom() const noexcept
{
	return (centerY() + (m_frect.h / 2));
}