#include "stdafx.h"
#include "game.h"
#include "sprite_sheet.h"

const std::string COMMON_LEVEL_MAP_PATH = "Levels/level_map_";

Game::Game() : m_is_running(false), m_is_fullscreen(false), m_screen(NULL), m_window(NULL), m_level(1), m_sprite_sheet(NULL)
{
}


Game::~Game()
{
}

bool Game::init()
{
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// get window, screen, renderer pointers
	m_window = SDL_CreateWindow("Fire Emblem?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	m_screen = SDL_GetWindowSurface(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	// load background level
	texture::load_texture_from_file(COMMON_LEVEL_MAP_PATH + std::to_string(level) + ".png", m_level_map, m_renderer);

	// load sprite atlas
	m_sprite_sheet = new SpriteSheet(m_renderer);
	
	m_is_running = true;
	std::cout << "Game initialized successfully." << std::endl;

	return true;
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

void Game::change_level()
{
}

