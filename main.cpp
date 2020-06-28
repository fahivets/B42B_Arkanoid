#include "stdafx.h"
#include "MainGame.h"
#include "utility/Vector2f.h"

int main(int argc, char* argv[])
{
	// test leaq stuff
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MainGame game;

	game.run();

	std::cout << "<<< QUIT GAME >>>" << std::endl;

	return (0);
}