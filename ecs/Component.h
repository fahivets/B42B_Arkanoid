#ifndef COMPONENT_H
#define COMPONENT_H
#include "stdafx.h"
#include "ECSHelper.h"

class Entity;

struct Component
{
    // A pointer to store the parent entity
    Entity* m_entity {nullptr};
    // Destructor
    virtual ~Component() = default;

    // Virtual functions
    virtual void init() = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(SDL_Renderer& rRender) = 0;
    virtual void handleInput(const Uint8* keys) = 0;
};

#endif