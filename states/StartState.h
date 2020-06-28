#ifndef STARTSTATE_H
#define STARTSTATE_H
#include "State.h"

class StartState : public State
{
public:
	// Constructors/Destructors
	StartState(MainGame& game);
	virtual ~StartState();

	// Functions
	void endState() override;
	void handleInput(const Uint8* keys) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& render) override;

private:

};

#endif