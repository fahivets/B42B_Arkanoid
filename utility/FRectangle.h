#ifndef FRECTANGLE_H
#define FRECTANGLE_H

/*
	OLD TODO dell
*/
struct FRectangle
{
	SDL_FRect m_frect;

	float centerX() const noexcept;
	float centerY() const noexcept;
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;
};

#endif
