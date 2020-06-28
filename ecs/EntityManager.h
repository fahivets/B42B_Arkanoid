#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "ECSHelper.h"
class Entity;

class EntityManager
{
public:
    // Constructor/Destructor
    EntityManager() = default;
    ~EntityManager() = default;

    // Functions
    void handleInput(const Uint8* keys);
    void update(const float& deltaTime);
    void render(SDL_Renderer& rRender);

    void refresh();
    void addToGroup(Entity* pEntity, Group group);
    Entity& addEntity();

    std::vector<Entity*>& getEntitiesByGroup(Group group);

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
    std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;

};

#endif