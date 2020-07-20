#include "stdafx.h"
#include "PlayingState.h"
#include "../MainGame.h"

PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
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

	ResourceHolder::get().audio.playMusic("test");
}

PlayingState::~PlayingState()
{}

void PlayingState::endState()
{

}

void PlayingState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_ESCAPE))
	{
		needPop(true);
	}
	// test sounds
	if (input.keyDown(SDL_SCANCODE_SPACE))
	{
		ResourceHolder::get().audio.pauseMusic();
	}
	if (input.keyDown(SDL_SCANCODE_R))
	{
		ResourceHolder::get().audio.resumeMusic();
	}
	if (input.mouseButtonDown(LEFT))
	{
		std::cout << "MOUSE PRESSED LEFT" << input.mousePos() << "\n";
	}
	if (input.mouseButtonDown(RIGHT))
	{
		std::cout << "MOUSE PRESSED RIGHT" << input.mousePos() << "\n";
	}

	m_entityManager.handleInput(input);
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
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

// Entity factory
void PlayingState::createBall()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH / 2 });
	entity.addComponent<BoxComponent>(Vector2f{ BALL::RADIUS * 2, BALL::RADIUS * 2 });
	entity.addComponent<PhysicsComponent>();
	entity.addComponent<RectangleComponent>(SDL_Color{ 255, 0, 0, 255 });
	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_velocity = Vector2f{ -BALL::VELOCITY, -BALL::VELOCITY };

	physics.outOfBounds = [&physics](const Vector2f& mSide)
	{
		if (mSide.x != 0.f)
		{
			physics.m_velocity.x = std::abs(physics.m_velocity.x) * mSide.x;
		}
		if (mSide.y != 0.f)
		{
			physics.m_velocity.y = std::abs(physics.m_velocity.y) * mSide.y;
		}
	};

	entity.addGroup(ArkanoidGroup::GBall);
}

void PlayingState::createPaddle()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH - 50 });
	entity.addComponent<BoxComponent>(Vector2f{ PADDLE::WIDTH, PADDLE::HEIGTH });
	entity.addComponent<PhysicsComponent>();

	// TODO tmp rectcomponent
	entity.addComponent<RectangleComponent>(SDL_Color{ 0, 0, 255, 255 });
	
	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "test");
	entity.addComponent<PaddleControlComponent>();
	
	entity.addGroup(ArkanoidGroup::GPaddle);
}

void PlayingState::createBrick(const Vector2f& rPosition)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(Vector2f{ BRICK::WIDTH, BRICK::HEIGTH });
	entity.addComponent<PhysicsComponent>();

	// TODO tmp rectcomponent
	entity.addComponent<RectangleComponent>(SDL_Color{ 255, 255, 0, 255 });
	// test fiasko texture
	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "none");
	
	entity.addGroup(ArkanoidGroup::GBrick);
}

// Collision
void PlayingState::testBPCollision(Entity& rBall, Entity& rPaddle) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& paddle(rPaddle.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball.box(), paddle.box()))
		return ;

	ball.m_velocity.y = -BALL::VELOCITY;
	if (ball.box().xCenter() < paddle.box().xCenter())
		ball.m_velocity.x = -BALL::VELOCITY;
	else
		ball.m_velocity.x = BALL::VELOCITY;
}

void PlayingState::testBBCollision(Entity& rBall, Entity& rBrick) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& brick(rBrick.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball.box(), brick.box()))
		return;

	rBrick.destroy();

	// How much the ball intersects the brick in every directions
	float overlapLeft{ ball.box().right() - brick.box().left() };
	float overlapRight{ ball.box().left() - brick.box().right() };
	float overlapTop{ ball.box().bottom() - brick.box().top() };
	float overlapBottom{ ball.box().top() - brick.box().bottom() };

	bool ballFromLeft{ abs(overlapLeft) < abs(overlapRight) };
	bool ballFromTop{ abs(overlapTop) < abs(overlapBottom) };

	float minOverlapX{ ballFromLeft ? (overlapLeft) : (overlapRight) };
	float minOverlapY{ ballFromTop ? (overlapTop) : (overlapBottom) };

	if (std::abs(minOverlapX) < std::abs(minOverlapY))
		ball.m_velocity.x = ballFromLeft ? -BALL::VELOCITY : BALL::VELOCITY;
	else
		ball.m_velocity.y = ballFromTop ? -BALL::VELOCITY : BALL::VELOCITY;
}