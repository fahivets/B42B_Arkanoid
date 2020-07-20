#include "stdafx.h"
#include "UIButtonComponent.h"
#include "Entity.h"

UIButtonComponent::UIButtonComponent(SDL_Renderer& rRenderer, TextureNameArray& rTextureNameArray)
{
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::NORMAL]);
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::HOVER]);
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::PRESSED]);

	m_buttonTextureArray[ButtonState::NORMAL] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::NORMAL]);
	m_buttonTextureArray[ButtonState::HOVER] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::HOVER]);
	m_buttonTextureArray[ButtonState::PRESSED] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::PRESSED]);
}

void UIButtonComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
	
	m_dstFRect = {
		m_pBoxComp->x(),
		m_pBoxComp->y(),
		m_pBoxComp->w(),
		m_pBoxComp->h(),
	};

}

void UIButtonComponent::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_buttonTextureArray[m_currentState], 0, &m_dstFRect);
}

void UIButtonComponent::update(const float& deltaTime)
{
	m_dstFRect = {
		m_pBoxComp->x(),
		m_pBoxComp->y(),
		m_pBoxComp->w(),
		m_pBoxComp->h(),
	};
}

void UIButtonComponent::handleInput(const InputManager& input)
{
	Vector2f mousePos = input.mousePos();
	SDL_Point point = {static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)};
	SDL_Rect rect = {
		static_cast<int>(m_dstFRect.x),
		static_cast<int>(m_dstFRect.y),
		static_cast<int>(m_dstFRect.w),
		static_cast<int>(m_dstFRect.h)
	};

	if (SDL_PointInRect(&point, &rect))
	{
		if (input.mouseButtonDown(LEFT) && !input.mouseButtonReleased(LEFT))
		{
			m_function();
			m_currentState = ButtonState::PRESSED;
		}
		else if (!input.mouseButtonPressed(LEFT))
		{

			m_currentState = ButtonState::HOVER;
		}
	
	}
	else
	{
		m_currentState = ButtonState::NORMAL;
	}
}

void UIButtonComponent::setFunction(std::function<void(void)> function)
{
	m_function = function;
}
