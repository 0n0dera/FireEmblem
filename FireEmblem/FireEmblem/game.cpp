#include "stdafx.h"
#include "game.h"
#include "sprite_sheet.h"
#include "Characters/swordsman.h"

Game::Game():
	level_(1), is_running_(false),is_fullscreen_(false),
	window_(SDL_CreateWindow("Fire Emblem?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals.SCREEN_WIDTH, globals.SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
	screen_(SDL_GetWindowSurface(window_)),
	renderer_(SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)),
	scene_(),camera_(),current_tile_(),current_player_(nullptr),game_state_(none),player_vector_(std::vector<Character*>())
{
}


Game::~Game()
{
}

bool Game::init()
{
	// load background level
	scene_.change_level_map(level_,renderer_);

	// load sprite sheets
	SpriteSheet::init_sprites(renderer_);

	// load players
	player_vector_.push_back(new Swordsman(0,0,true));

	is_running_ = true;
	std::cout << "Game initialized successfully." << std::endl;

	return true;
}

void Game::main_loop()
{
	uint32_t next_game_tick = SDL_GetTicks();
	int loops;

	while (is_running_)
	{
		handle_events();
		loops = 0;
		while(SDL_GetTicks() > next_game_tick && loops < globals.MAX_FRAMESKIP)
		{
			update();
			next_game_tick += globals.SKIP_TICKS;
			loops++;
		}
		draw();
	}
}

void Game::clean()
{
	SDL_FreeSurface(screen_);
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
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
				if (game_state_ == player_move)
				{
					break;
				}
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit();
						break;
					//case SDLK_F4:
					//	toggle_fullscreen();
					//	break;
					case SDLK_DOWN:
						inc_cur_tile_y(globals.TILE_SIZE);
						break;
					case SDLK_UP:
						inc_cur_tile_y(-globals.TILE_SIZE);
						break;
					case SDLK_RIGHT:
						inc_cur_tile_x(globals.TILE_SIZE);
						break;
					case SDLK_LEFT:
						inc_cur_tile_x(-globals.TILE_SIZE);
						break;
					case SDLK_z:
						handle_z_press();
				}
				break;

		}
	}
}

void Game::update()
{
	if (game_state_ == player_move)
	{
		move_player();
	}
}

void Game::draw()
{
	scene_.draw_level_map(camera_, renderer_);

	if (game_state_ == player_select)
	{
		scene_.draw_movement_grid(current_player_,renderer_);
	}
	for (auto it = player_vector_.begin(); it != player_vector_.end(); ++it)
	{
		(*it)->draw(camera_,renderer_);
	}
	for (auto it = enemy_vector_.begin(); it != enemy_vector_.end(); ++it)
	{
		(*it)->draw(camera_,renderer_);
	}

	if (game_state_ != player_move)
	{
		highlight_cur_tile();
	}

	SDL_RenderPresent(renderer_);
}


void Game::quit()
{
	is_running_ = false;
}

void Game::toggle_fullscreen()
{
	if (!is_fullscreen_)
		SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(window_, 0);
	is_fullscreen_ = !is_fullscreen_;
}

void Game::change_level()
{
}

void Game::highlight_cur_tile()
{
	SDL_SetRenderDrawColor(renderer_,255,0,0,255);
	SDL_Rect cur_tile_rect = {current_tile_.get_screen_x(),current_tile_.get_screen_y(),globals.TILE_SIZE,globals.TILE_SIZE};
	SDL_RenderDrawRect(renderer_, &cur_tile_rect);
}

void Game::inc_cur_tile_x(int amount)
{
	int new_tile_x = current_tile_.get_actual_x() + amount;
	if (new_tile_x < scene_.get_level_map_width() && new_tile_x >= 0)
	{
		if (new_tile_x >= camera_.get_camera_x_bound())
		{
			camera_.inc_camera_x();
		}
		else if (new_tile_x < camera_.get_camera_x())
		{
			camera_.dec_camera_x();
		}
		else
		{
			current_tile_.inc_screen_x(amount);
		}
		current_tile_.inc_actual_x(amount);
	}
}

void Game::inc_cur_tile_y(int amount)
{
	int new_tile_y = current_tile_.get_actual_y() + amount;
	if (new_tile_y < scene_.get_level_map_height() && new_tile_y >= 0)
	{
		if (new_tile_y >= camera_.get_camera_y_bound())
		{
			camera_.inc_camera_y();
		}
		else if (new_tile_y < camera_.get_camera_y())
		{
			camera_.dec_camera_y();
		}
		else
		{
			current_tile_.inc_screen_y(amount);
		}
		current_tile_.inc_actual_y(amount);
	}
}

void Game::handle_z_press()
{
	switch (game_state_)
	{
		case none:
			for (auto it = player_vector_.begin(); it != player_vector_.end(); ++it)
			{
				if (current_tile_.get_actual_x() == (*it)->get_x() && current_tile_.get_actual_y() == (*it)->get_y())
				{
					game_state_ = player_select;
					current_player_ = (*it);
					current_player_->set_state(Character::selected);
					scene_.movement_grid_not_ready();
					break;
				}
			}
			break;
		case player_select:
			game_state_ = player_move;
			break;
		case player_done:
			game_state_ = none;
			current_player_->set_state(Character::idle);
			break;
	}
}

void Game::move_player()
{
	int x_diff = current_player_->get_x() - current_tile_.get_actual_x();
	int y_diff = current_player_->get_y() - current_tile_.get_actual_y();

	if (x_diff == 0 && y_diff == 0)
	{
		after_player_move();
		return;
	}

	if (x_diff < 0)
	{
		current_player_->set_state(Character::move_right);
	}
	else if (x_diff > 0)
	{
		current_player_->set_state(Character::move_left);
	}
	else if (y_diff < 0)
	{
		current_player_->set_state(Character::move_down);
	}
	else if (y_diff > 0)
	{
		current_player_->set_state(Character::move_up);
	}
	
	current_player_->move();
}

void Game::after_player_move()
{
	game_state_ = player_done;
	current_player_->set_state(Character::selected);
}