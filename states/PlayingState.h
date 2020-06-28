#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H
#include "State.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

// ECS includes
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"
#include "ecs/PositionComponent.h"
#include "ecs/PhysicsComponent.h"
#include "ecs/RectangleComponent.h"
#include "ecs/PaddleControlComponent.h"

class PlayingState : public State
{
public:
	// Use enum for groups to keep track of our entities
	enum ArkanoidGroup : std::size_t
	{
		GPaddle,
		GBrick,
		GBall
	};


	// Constructors/Destructors
	PlayingState(MainGame& rGame);
	virtual ~PlayingState();

	// Functions
	void endState() override;
	void handleInput(const Uint8* keys) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;

private:
	EntityManager m_entityManager;

//	Ball* m_ball;
//	Paddle* m_paddle;
//	std::vector<Brick> m_bricks;
	
	// Entity factory
	Entity& createBall();
	Entity& createPaddle();
	Entity& createBrick(const Vector2f& rPosition);

	void testBPCollision(Entity& rBall, Entity& rPaddle) noexcept;
	void testBBCollision(Entity& rBall , Entity& rBrick) noexcept;
	// old test collis
	void testCollision(Ball& ball, Paddle& paddle) noexcept;
	void testCollision(Ball& ball, Brick& brick) noexcept;

	template <class T1, class T2>
	bool isIntersecting(T1& rA, T2& rB) noexcept;
};

// Template functions
template <class T1, class T2>
bool PlayingState::isIntersecting(T1& rA, T2& rB) noexcept
{
	return (rA.right() >= rB.left() && rA.left() <= rB.right() &&
		rA.bottom() >= rB.top() && rA.top() <= rB.bottom());
}
#endif