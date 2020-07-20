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
    virtual void init() {};
    virtual void update(const float& deltaTime) {};
    virtual void render(SDL_Renderer& rRender) {};
  //  virtual void handleInput(const Uint8* keys) {};
    virtual void handleInput(const InputManager& input) {};
};

#endif