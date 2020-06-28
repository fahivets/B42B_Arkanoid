#ifndef ENTITY_H
#define ENTITY_H
#include "ECSHelper.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "RectangleComponent.h"
#include "PaddleControlComponent.h"
#include "EntityManager.h"

//struct Component;
class EntityManager;

class Entity
{
public:
    // Constructor/Destructor
    Entity(EntityManager& rManager);
    ~Entity() = default;

    // Functions
    void handleInput(const Uint8* keys);
    void update(const float& deltaTime);
    void render(SDL_Renderer& rRender);

    // Some methods to control the lifetime of the entity
    bool isAlive() const;
    void destroy();
    
    // Methods for working with Groups
    bool hasGroup(Group group) const noexcept;
    void addGroup(Group group) noexcept;
    void delGroup(Group group) noexcept;

    // Template methods for working with Components
    template <typename T>
    bool hasComponent() const;

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... rrArgs);

    template <typename T>
    T& getComponent() const;

private:
    EntityManager& m_rManager;

	bool m_alive{ true };
	std::vector<std::unique_ptr<Component>> m_components;
   
    // Arrays to quickly get a component with a specific ID
    ComponentArray m_componentArray;

    // Bitset to check the existance of a component with a specific ID
    ComponentBitset m_componentBitset;
    
    // Bitset to our entities
    GroupBitset m_groupBitset;
};

/*
    Template methods implementation
*/

template <typename T>
bool Entity::hasComponent() const
{
    /*
        @return bool
        Check if this entity has a component, just request a set of bits.
    */
    return m_componentBitset[getComponentTypeID<T>()];
}

template <typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... rrArgs)
{
    /*
        @return  T& - a reference to the newly added component
        
        Add new component to components/
    */
    
    // Before adding a component, checking if it already exist
    assert(!hasComponent<T>());

    // Allocating the component of type <T>
    // on the heap, by forwarding the passed arguments to its constructor.
    T* component(new T(std::forward<TArgs>(rrArgs)...));
   
    // Set the component's entity to the current instance.
    component->m_entity = this;
    
    // Wrap the raw pointer into a smart one
    std::unique_ptr<Component> uPtr{ component };

    // Add the smart pointer to our container
    // <std::unique_ptr> cannot be copied, so we use <std::move>
    m_components.emplace_back(std::move(uPtr));

    // Adding new component to the bitset and to the array.
    m_componentArray[getComponentTypeID<T>()] = component;
    m_componentBitset[getComponentTypeID<T>()] = true;

    // Called Component::init()
    component->init();

    return (*component);
}

template <typename T>
T& Entity::getComponent() const
{
    /*
        @return T&

        Retrieving a specific component from the array
    */
    
    // Assert its existance
    assert(hasComponent<T>());

    auto ptr(m_componentArray[getComponentTypeID<T>()]);

    return (*static_cast<T*>(ptr));
}

#endif