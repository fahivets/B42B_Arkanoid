#ifndef STARTSTATE_H
#define STARTSTATE_H
#include "State.h"

// ECS includes
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"

class StartState : public State
{
public:
	// Use enum for groups to keep track of our entities
	enum ArkanoidGroup : std::size_t
	{
		GPaddle,
		GBrick,
		GBall,
		GButton
	};
	// Constructors/Destructors
	StartState(MainGame& game);
	virtual ~StartState();

	// Functions
	void endState() override;
//	void handleInput(const Uint8* keys) override;
	void handleInput(const InputManager& input) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;

private:
	// Entity factory
	void createButton(const Vector2f& rPosition, const Vector2f& rSize);

private:
	EntityManager m_entityManager;

};

#endif