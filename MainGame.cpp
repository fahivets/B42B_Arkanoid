#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	if (m_display.getStatus())
	{
		m_isRunning = true;

		// init starting textures (maybe move this in to current the state)
		ResourceHolder::get().textures.init(m_display.getRenderer());
		// init starting fonts (maybe move this in to current the state)
		ResourceHolder::get().fonts.init();
		// init starting audio (maybe move this in to current the state)
		ResourceHolder::get().audio.init();


		pushState<StartState>(*this);
	}
}

MainGame::~MainGame()
{
	m_isRunning = false;
	// Remove all states
	while (!m_states.empty())
	{
		m_states.pop();
	}
}

bool MainGame::isRunning() const
{
	return (m_isRunning);
}

void MainGame::update(const float deltaTime)
{

	m_states.top()->update(deltaTime);
}

void MainGame::handleInput()
{
//	SDL_PumpEvents();
//	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	// TEST new input
	m_input.update();

	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			m_isRunning = false;
		}
	}

	//m_states.top()->handleInput(keys);
	m_states.top()->handleInput(m_input);
}

void MainGame::render()
{
	SDL_RenderClear(&m_display.getRenderer());

	m_states.top()->render(m_display.getRenderer());

	SDL_RenderPresent(&m_display.getRenderer());
}

void MainGame::run()
{
	float deltaTime{ 0.0f };
	float lag{ 0.0f };

	//Game loop		
	while (isRunning() && !m_states.empty())
	{	
		// Handle Input
		handleInput();

		lag += deltaTime;
		while (lag >= constFTimeSlice)
		{
			// Update
			update(constFTimeStep);

			lag -= constFTimeSlice;
		}
		
		// Render
		render();

		// Update states status and pop it
		updateState();

		// Update prev input
		m_input.updatePrevInput();

		// Update delta time every frame
		deltaTime = m_timer.getDelta();

		// TPM Update Window Title
		std::string title = "FT: " + std::to_string(deltaTime) + "\t FPS : " + std::to_string(m_timer.getFPS(deltaTime));
		SDL_SetWindowTitle(&m_display.getWindow(), title.c_str());
	}
}

void MainGame::updateState()
{
	if (m_states.top()->checkForQuit())
	{
		m_states.top()->endState();
		m_states.pop();
	}
}

void MainGame::pushState(std::unique_ptr<State> state)
{
	m_states.push(std::move(state));
}

SDL_Window& MainGame::getWindow() const
{
	return (m_display.getWindow());
}

SDL_Renderer& MainGame::getRenderer() const
{
	return (m_display.getRenderer());
}

State& MainGame::getCurrentState()
{
	return (*m_states.top());
}
