#include "stdafx.h"
#include "game.h"
#include "sprite_sheet.h"
#include "Characters/swordsman.h"

Game::Game():
	level_(1), game_state_(none), is_running_(false),is_fullscreen_(false),
	window_(SDL_CreateWindow("Fire Emblem?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals.SCREEN_WIDTH, globals.SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
	screen_(SDL_GetWindowSurface(window_)),
	renderer_(SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)),
	scene_(renderer_),camera_(),current_tile_(),player_vector_(std::vector<Character*>()),enemy_vector_(std::vector<Character*>()), current_player_(nullptr),
	saved_player_x_(0),saved_player_y_(0), saved_camera_x_(0), saved_camera_y_(0)
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

	// load enemies
	enemy_vector_.push_back(new Swordsman(0,3,false));
	enemy_vector_.push_back(new Swordsman(2,0,false));
	enemy_vector_.push_back(new Swordsman(1,0,false));
	enemy_vector_.push_back(new Swordsman(0,2,false));
	enemy_vector_.push_back(new Swordsman(1,2,false));
	enemy_vector_.push_back(new Swordsman(1,3,false));

	update_enemy_positions();

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
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit();
					break;
					//case SDLK_F4:
					//	toggle_fullscreen();
					//	break;
				case SDLK_DOWN:
					handle_down_press();
					inc_cur_tile_y(globals.TILE_SIZE);
					break;
				case SDLK_UP:
					handle_up_press();
					inc_cur_tile_y(-globals.TILE_SIZE);
					break;
				case SDLK_RIGHT:
					handle_right_press();
					inc_cur_tile_x(globals.TILE_SIZE);
					break;
				case SDLK_LEFT:
					handle_left_press();
					inc_cur_tile_x(-globals.TILE_SIZE);
					break;
				case SDLK_z:
					handle_z_press();
					break;
				case SDLK_x:
					handle_x_press();
					break;
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
		scene_.draw_movement_grid(current_player_,camera_,enemy_vector_,renderer_);
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
	SDL_Rect cur_tile_rect = {current_tile_.get_actual_x()-camera_.get_camera_x(),current_tile_.get_actual_y()-camera_.get_camera_y(),globals.TILE_SIZE,globals.TILE_SIZE};
	SDL_RenderDrawRect(renderer_, &cur_tile_rect);
}

void Game::inc_cur_tile_x(int amount)
{
	if (game_state_ == none || game_state_ == player_select)
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
			current_tile_.inc_actual_x(amount);
		}
	}	
}

void Game::inc_cur_tile_y(int amount)
{
	if (game_state_ == none || game_state_ == player_select)
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
			current_tile_.inc_actual_y(amount);
		}
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
				saved_player_x_ = current_player_->get_x();
				saved_player_y_ = current_player_->get_y();
				saved_camera_x_ = camera_.get_camera_x();
				saved_camera_y_ = camera_.get_camera_y();
				return;
			}
		}
		break;
	case player_select:
		for (auto it = player_vector_.begin(); it != player_vector_.end(); ++it)
		{
			if ((*it)!=current_player_ && (*it)->get_x() == current_tile_.get_actual_x() && (*it)->get_y() == current_tile_.get_actual_y())
			{
				return;
			}		
		}
		for (auto it = scene_.move_tiles_.begin(); it != scene_.move_tiles_.end(); ++it)
		{
			if ((*it).first == current_tile_.get_actual_x() && (*it).second == current_tile_.get_actual_y())
			{
				game_state_ = player_move;
				return;
			}
		}
		break;
	case player_done:
		game_state_ = none;
		current_player_->set_state(Character::idle);
		scene_.movement_grid_not_ready();
		break;
	}
}

void Game::handle_x_press()
{
	switch (game_state_)
	{
		case player_select:
			game_state_ = none;
			scene_.movement_grid_not_ready();
			current_player_->set_state(Character::idle);
			reset_camera();
			break;
		case player_done:
			game_state_ = player_select;
			current_player_->set_state(Character::selected);
			current_player_->set_x(saved_player_x_);
			current_player_->set_y(saved_player_y_);
			reset_camera();
			break;

	}
}

void Game::handle_down_press()
{

}

void Game::handle_up_press()
{

}

void Game::handle_right_press()
{

}

void Game::handle_left_press()
{

}

void Game::reset_camera()
{
	current_tile_.set_actual_x(current_player_->get_x());
	current_tile_.set_actual_y(current_player_->get_y());
	camera_.set_camera_x(saved_camera_x_);
	camera_.set_camera_y(saved_camera_y_);
}

void Game::update_enemy_positions()
{
	for (auto it = enemy_vector_.begin(); it != enemy_vector_.end(); ++it)
	{
		scene_.impassable_terrain_[(*it)->get_y() / globals.TILE_SIZE*scene_.get_level_map_width_tiles() + (*it)->get_x()/globals.TILE_SIZE] = 1;
	}
	std::cout << std::endl;
	for (int i = 0; i < scene_.get_level_map_height_tiles(); i++)
	{
		for (int j = 0; j < scene_.get_level_map_width_tiles(); j++)
		{
			std::cout << scene_.impassable_terrain_[i*scene_.get_level_map_width_tiles() + j];
		}
		std::cout << std::endl;
	}
}