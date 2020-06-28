#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

class DisplayManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	DisplayManager();
	~DisplayManager();

	// Functions
	SDL_Window& getWindow() const;
	SDL_Renderer& getRenderer() const;
	bool getStatus() const;

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_status;

	// Init Private Functions
	void initVariables();
	bool initSDL();
	bool initWindow();
	bool initRenderer();
	void quit();
};

#endif
