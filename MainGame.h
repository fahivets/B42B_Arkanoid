#ifndef MAINGAME_H
#define MAINGAME_H
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"
#include "utility/Timer.h"
#include "managers/DisplayManager.h"
#include "managers/ResourceHolder.h"
#include "managers/InputManager.h"
#include "states/StartState.h"

constexpr float constFTimeStep{ 1.0f };
constexpr float constFTimeSlice{ 1.0f };

class MainGame : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	MainGame();
	~MainGame();

	// Accessors
	bool isRunning() const;

	// Functions
	void update(const float deltaTime);
	void handleInput();
	void render();
	void run();
	void updateState();

	template<typename T, typename... Args>
	void pushState(Args&&... args);
	void pushState(std::unique_ptr<State> state);
//	template<typename T, typename... Args>
//	void changeState(Args&&... args);

	SDL_Window& getWindow() const;
	SDL_Renderer& getRenderer() const;

private:
	bool m_isRunning;

	Timer m_timer;
	std::stack<std::unique_ptr<State>> m_states;
//	std::unique_ptr<State> m_changeState;

	// make Display class adn InputHandler class
	DisplayManager m_display;
	InputManager m_input;
	SDL_Event m_event;


	State& getCurrentState();
};

// Template functions

template<typename T, typename... Args>
inline void MainGame::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

/*
template<typename T, typename ...Args>
inline void MainGame::changeState(Args&& ...args)
{
	m_change = std::make_unique<T>(std::forward<Args>(args)...);
}
*/
#endif