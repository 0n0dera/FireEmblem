#include "stdafx.h"
#include "Game.h"


Game::Game() : m_is_running(false), m_is_fullscreen(false), m_screen(NULL), m_window(NULL)
{
}


Game::~Game()
{
}

void Game::init()
{
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Fire Emblem: Not Actually", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	m_screen = SDL_GetWindowSurface(m_window);

	m_is_running = true;

	std::cout << "Game initialized successfully." << std::endl;
}

void Game::main_loop()
{
	while (m_is_running)
	{
		handle_events();
		update();
		draw();
	}
}

void Game::clean()
{
	SDL_FreeSurface(m_screen);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::handle_events()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type) {
			
			case SDL_QUIT:
				quit();
				break;
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit();
						break;
					//case SDLK_F4:
					//	toggle_fullscreen();
					//	break;
				}
				break;

		}
	}
}

void Game::update()
{
}

void Game::draw()
{
}

void Game::quit()
{
	m_is_running = false;
}

void Game::toggle_fullscreen()
{
	if (!m_is_fullscreen)
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(m_window, 0);
	m_is_fullscreen = !m_is_fullscreen;
}
