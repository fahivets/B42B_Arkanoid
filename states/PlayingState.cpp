#include "stdafx.h"
#include "PlayingState.h"



PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
//	m_ball = new Ball(DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH / 2);
//	m_paddle = new Paddle(DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH - 50);

	createBall();
	createPaddle();

	// create 44 bricks
	for (int iX = 0; iX < BRICK::COUNT_X; ++iX)
	{
		for (int iY = 0; iY < BRICK::COUNT_Y; ++iY)
		{
			createBrick(Vector2f{ (iX + 1) * (BRICK::WIDTH + 3) + 22, (iY + 2) * (BRICK::HEIGTH + 3) });
		}
	}
}

PlayingState::~PlayingState()
{
//	delete m_ball;
//	delete m_paddle;
//	m_ball = nullptr;
//	m_paddle = nullptr;
}

void PlayingState::endState()
{

}

void PlayingState::handleInput(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_ESCAPE])
	{
		needPop(true);
	}

	m_entityManager.handleInput(keys);
}

void PlayingState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);
	
	auto& balls(m_entityManager.getEntitiesByGroup(GBall));
	auto& paddles(m_entityManager.getEntitiesByGroup(GPaddle));
	auto& bricks(m_entityManager.getEntitiesByGroup(GBrick));

	for (auto& ball : balls)
	{
		for (auto& paddle : paddles)
		{
			testBPCollision(*ball, *paddle);
		}
		for (auto& brick : bricks)
		{
			testBBCollision(*ball, *brick);
		}
	}

	/* old ver
	m_ball->update(deltaTime);
	m_paddle->update(deltaTime);

	testCollision(*m_ball, *m_paddle);

	for (auto& brick : m_bricks)
	{
		testCollision(*m_ball, brick);
	}

	// STL algoorithms + lambda
	m_bricks.erase(std::remove_if(begin(m_bricks), end(m_bricks),
			[](const Brick& brick)
			{
				return (brick.isDestroyed());
			}),
			end(m_bricks));
	*/
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
	/* old
	m_ball->render(rRender);
	m_paddle->render(rRender);
	for (auto& brick : m_bricks)
		brick.render(rRender);
	*/
}

// Entity factory
Entity& PlayingState::createBall()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH / 2 });
	entity.addComponent<PhysicsComponent>(Vector2f{ BALL::RADIUS * 2, BALL::RADIUS * 2 });
	entity.addComponent<RectangleComponent>(Vector2f{ BALL::RADIUS * 2, BALL::RADIUS * 2 }, SDL_Color{ 255, 0, 0, 255 });

	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_velocity = Vector2f{ -BALL::VELOCITY, -BALL::VELOCITY };

	// TEST
	physics.outOfBounds = [&physics](const Vector2f& mSide)
	{
		if (mSide.x != 0.f)
			physics.m_velocity.x =
			std::abs(physics.m_velocity.x) * mSide.x;

		if (mSide.y != 0.f)
			physics.m_velocity.y =
			std::abs(physics.m_velocity.y) * mSide.y;
	};


	entity.addGroup(ArkanoidGroup::GBall);
	return (entity);
}

Entity& PlayingState::createPaddle()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH - 50 });
	entity.addComponent<PhysicsComponent>(Vector2f{ PADDLE::WIDTH, PADDLE::HEIGTH });
	entity.addComponent<RectangleComponent>(Vector2f{ PADDLE::WIDTH, PADDLE::HEIGTH }, SDL_Color{ 0, 0, 255, 255 });
	entity.addComponent<PaddleControlComponent>();
	
//	auto& physics(entity.getComponent<PhysicsComponent>());
//	physics.m_velocity = Vector2f{ PADDLE::VELOCITY, PADDLE::VELOCITY };

	entity.addGroup(ArkanoidGroup::GPaddle);

	return (entity);
}

Entity& PlayingState::createBrick(const Vector2f& rPosition)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<PhysicsComponent>(Vector2f{ BRICK::WIDTH, BRICK::HEIGTH });
	entity.addComponent<RectangleComponent>(Vector2f{ BRICK::WIDTH, BRICK::HEIGTH }, SDL_Color{ 255, 255, 0, 255 });

	entity.addGroup(ArkanoidGroup::GBrick);

	return (entity);
}

//NEW collision
void PlayingState::testBPCollision(Entity& rBall, Entity& rPaddle) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& paddle(rPaddle.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball, paddle))
		return ;

	ball.m_velocity.y = -BALL::VELOCITY;
	if (ball.x() < paddle.x())
		ball.m_velocity.x = -BALL::VELOCITY;
	else
		ball.m_velocity.x = BALL::VELOCITY;

	/*
	ball.setDirY(-1.0f);
	if (ball.x() < paddle.x())
		ball.setDirX(-1.0f);
	else
		ball.setDirX(1.0f);
	*/
}

void PlayingState::testBBCollision(Entity& rBall, Entity& rBrick) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& brick(rBrick.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball, brick))
		return;

	rBrick.destroy();

	// How much the ball intersects the brick in every directions
	float overlapLeft{ ball.right() - brick.left() };
	float overlapRight{ ball.left() - brick.right() };
	float overlapTop{ ball.bottom() - brick.top() };
	float overlapBottom{ ball.top() - brick.bottom() };

	bool ballFromLeft{ abs(overlapLeft) < abs(overlapRight) };
	bool ballFromTop{ abs(overlapTop) < abs(overlapBottom) };

	float minOverlapX{ ballFromLeft ? (overlapLeft) : (overlapRight) };
	float minOverlapY{ ballFromTop ? (overlapTop) : (overlapBottom) };

	if (std::abs(minOverlapX) < std::abs(minOverlapY))
		ball.m_velocity.x = ballFromLeft ? -BALL::VELOCITY : BALL::VELOCITY;
	else
		ball.m_velocity.y = ballFromTop ? -BALL::VELOCITY : BALL::VELOCITY;
	/*
	if (abs(minOverlapX) < abs(minOverlapY))
	{
		float newDirX = ballFromLeft ? (-1.0f) : (1.0f);
		ball.setDirX(newDirX);
	}
	else
	{
		float newDirY = ballFromTop ? (-1.0f) : (1.0f);
		ball.setDirY(newDirY);
	}
	*/
}
// old collision
void PlayingState::testCollision(Ball& ball, Paddle& paddle) noexcept
{
	if (!isIntersecting(ball, paddle))
		return ;

	ball.setDirY(-1.0f);

	if (ball.centerX() < paddle.centerX())
		ball.setDirX(-1.0f);
	else
		ball.setDirX(1.0f);
}

void PlayingState::testCollision(Ball& ball, Brick& brick) noexcept
{
	if (!isIntersecting(ball, brick))
		return ;

	brick.destroy();

	// How much the ball intersects the brick in every directions
	float overlapLeft{ ball.right() - brick.left() };
	float overlapRight{ ball.left() - brick.right() };
	float overlapTop{ ball.bottom() - brick.top() };
	float overlapBottom{ ball.top() - brick.bottom() };


	bool ballFromLeft{ abs(overlapLeft) < abs(overlapRight) };
	bool ballFromTop{ abs(overlapTop) < abs(overlapBottom) };

	float minOverlapX{ ballFromLeft ? (overlapLeft) : (overlapRight) };
	float minOverlapY{ ballFromTop ? (overlapTop) : (overlapBottom) };

	if (abs(minOverlapX) < abs(minOverlapY))
	{
		float newDirX = ballFromLeft ? (-1.0f) : (1.0f);
		ball.setDirX(newDirX);
	}
	else
	{
		float newDirY = ballFromTop ? (-1.0f) : (1.0f);
		ball.setDirY(newDirY);
	}
}
