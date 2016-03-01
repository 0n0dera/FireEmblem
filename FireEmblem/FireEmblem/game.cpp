#include "stdafx.h"
#include "game.h"
#include "sprite_sheet.h"

const int SCREEN_WIDTH = 870;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 30;

Game::Game():COMMON_LEVEL_MAP_PATH("Levels/level_map_"), m_window(NULL), m_screen(NULL),m_renderer(NULL),m_level_map(NULL)
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
	m_window = SDL_CreateWindow("Fire Emblem?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_screen = SDL_GetWindowSurface(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	// load background level
	texture::load_texture_from_file(COMMON_LEVEL_MAP_PATH + std::to_string(m_level) + ".png", m_level_map, m_renderer);
	
	// load sprite sheets
	SpriteSheet::init_sprites(m_renderer);

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
	SDL_DestroyTexture(m_level_map);
	SDL_DestroyRenderer(m_renderer);
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
	draw_level_map();
}

void Game::draw_level_map()
{
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_level_map, NULL, NULL);
	for (int i = 0; i < SCREEN_WIDTH; i += TILE_SIZE)
	{
		SDL_RenderDrawLine(m_renderer, i, 0, i, SCREEN_HEIGHT);
		SDL_RenderDrawLine(m_renderer, 0, i, SCREEN_WIDTH, i);
	}
	SDL_RenderPresent(m_renderer);
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

