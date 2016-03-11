#include "stdafx.h"
#include "sprite_sheet.h"
#include "character.h"
#include "stats.h"
#include "game.h"

Game::Game():
	level_(1), game_state_(none), is_running_(false),is_fullscreen_(false),
	window_(SDL_CreateWindow("Fire Emblem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals.SCREEN_WIDTH, globals.SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
	screen_(SDL_GetWindowSurface(window_)),
	renderer_(SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)),
	scene_(renderer_),camera_(),current_tile_(),player_vector_(std::vector<std::shared_ptr<Character>>()),enemy_vector_(std::vector<std::shared_ptr<Character>>()), character_map_(std::vector<Character*>(scene_.get_level_map_height_tiles()*scene_.get_level_map_width_tiles())),
	current_player_(std::shared_ptr<Character>()), saved_camera_x_(0), saved_camera_y_(0), active_players_(0), player_menu_(), active_enemies_(0), mc_(std::shared_ptr<Character>())
{
}


Game::~Game()
{
}

/************************* PUBLIC METHODS **************************/

bool Game::init()
{
	// load background level
	scene_.change_level_map(level_,renderer_);

	// load sprite sheets
	SpriteSheet::init_sprites(renderer_);

	create_players();
	update_player_positions();
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

/************************* CORE METHODS **************************/

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
					break;
				case SDLK_UP:
					handle_up_press();
					break;
				case SDLK_RIGHT:
					handle_right_press();
					break;
				case SDLK_LEFT:
					handle_left_press();
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
	switch (game_state_)
	{
		case none:
			if (character_map_[get_unit_array_pos(current_tile_.get_actual_x(), current_tile_.get_actual_y())] != nullptr
				&& !character_map_[get_unit_array_pos(current_tile_.get_actual_x(), current_tile_.get_actual_y())]->is_grey()
				&& character_map_[get_unit_array_pos(current_tile_.get_actual_x(), current_tile_.get_actual_y())]->is_player())
			{
				current_tile_.set_frame_max();
			}
			else
			{
				current_tile_.inc_frame();
			}
			break;
		case player_select:
			current_tile_.inc_frame();
			break;
		case player_move:
			move_player();
			break;
		case player_attack:
			break;
		case enemy_move:
			move_enemy();
	}
}

void Game::draw()
{
	scene_.draw_level_map(camera_, renderer_);

	if (game_state_ == player_select)
	{
		scene_.draw_movement_grid(current_player_,camera_,renderer_);
	}

	if (game_state_ == player_attack || (game_state_ == player_menu && player_menu_.get_selection() == 0))
	{
		scene_.draw_attack_range(current_player_,camera_,renderer_);
	}
	
	draw_characters();

	if (game_state_==none || game_state_==player_select || game_state_ == player_attack)
	{
		scene_.draw_selected_tile(current_tile_.get_actual_x()-camera_.get_camera_x()-current_tile_.get_frame(),current_tile_.get_actual_y()-camera_.get_camera_y()-current_tile_.get_frame(),2*current_tile_.get_frame(),game_state_==player_attack,renderer_);
	}


	if (game_state_ == player_menu || game_state_ == player_done)
	{
		player_menu_.draw(current_player_->get_x()-camera_.get_camera_x() > globals.SCREEN_WIDTH/2,current_player_,scene_,renderer_);
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


/************************* MOVEMENT RELATED METHODS **************************/

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
		after_move_player();
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

void Game::after_move_player()
{
	game_state_ = player_menu;
	player_menu_.set_can_attack(check_enemies_in_range());
}

void Game::move_enemy()
{
}

void Game::after_move_enemy()
{
	// if enemy plans on attack, attack
	// otherwise, unit is done
}

void Game::reset_camera(const std::shared_ptr<Character>& unit)
{
	unit->set_x(unit->get_old_x());
	unit->set_y(unit->get_old_y());
	current_tile_.set_actual_x(unit->get_old_x());
	current_tile_.set_actual_y(unit->get_old_y());
	camera_.set_camera_x(saved_camera_x_);
	camera_.set_camera_y(saved_camera_y_);
}


/************************* BUTTON PRESS HANDLER METHODS **************************/

void Game::handle_z_press()
{
	switch (game_state_)
	{
		case none:
		{
			Character* temp = character_map_[get_unit_array_pos(current_tile_.get_actual_x(),current_tile_.get_actual_y())];
			if (temp != nullptr && temp->is_player() && !temp->is_grey())
			{
				game_state_ = player_select;
				current_player_.reset(temp);
				current_player_->set_state(Character::selected);
				current_player_->set_old_x(current_player_->get_x());
				current_player_->set_old_y(current_player_->get_y());
				saved_camera_x_ = camera_.get_camera_x();
				saved_camera_y_ = camera_.get_camera_y();
				return;
			}
			else if (temp == nullptr || temp->is_grey())
			{
				game_state_ = turn_menu;
			}
			break;
		}
		case player_select:
		{
			for (auto it = scene_.move_tiles_.begin(); it != scene_.move_tiles_.end(); ++it)
			{
				if ((*it).first == current_tile_.get_actual_x() && (*it).second == current_tile_.get_actual_y())
				{
					if (character_map_[get_unit_array_pos(current_tile_.get_actual_x(),current_tile_.get_actual_y())] == nullptr || 
						character_map_[get_unit_array_pos(current_tile_.get_actual_x(),current_tile_.get_actual_y())] == current_player_.get())
					{
						game_state_ = player_move;
						return;
					}
				}
			}
			break;
		}
		case player_menu:
		case player_done:
			switch (player_menu_.get_selection())
			{
				case PlayerMenu::MenuSelection::wait:
					game_state_ = none;
					unit_is_done(current_player_);
					scene_.movement_grid_not_ready();
					break;
				case PlayerMenu::MenuSelection::atk_or_heal:
					game_state_ = player_attack;
					break;
				case PlayerMenu::MenuSelection::item:
					break;
			}
			break;
		case turn_menu:
			game_state_ = enemy_move;
			active_players_ = 0;
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
			reset_camera(current_player_);
			break;
		case player_menu:
			game_state_ = player_select;
			current_player_->set_state(Character::selected);
			reset_camera(current_player_);
			break;
		case player_attack:
			game_state_ = player_menu;
			break;
		case turn_menu:
			game_state_ = none;
			break;

	}
}

void Game::handle_down_press()
{
	switch (game_state_)
	{
		case none:
		case player_select:
			inc_cur_tile_y(globals.TILE_SIZE);
			break;
		case player_menu:
		case player_done:
			player_menu_.inc_selection(1);
			break;
	}
}

void Game::handle_up_press()
{
	switch (game_state_)
	{
		case none:
		case player_select:
			inc_cur_tile_y(-globals.TILE_SIZE);
			break;
		case player_menu:
		case player_done:
			player_menu_.inc_selection(-1);
			break;
	}
}

void Game::handle_right_press()
{
	switch (game_state_)
	{
		case none:
		case player_select:
			inc_cur_tile_x(globals.TILE_SIZE);
			break;
	}
}

void Game::handle_left_press()
{
	switch (game_state_)
	{
		case none:
		case player_select:
			inc_cur_tile_x(-globals.TILE_SIZE);
			break;
	}
}


/************************* MENU/ATTACK RELATED METHODS **************************/

bool Game::check_enemies_in_range()
{
	// check if enemies can be attacked
	int max_atk = current_player_->get_max_attack_range();
	for (int i= -max_atk; i<=max_atk;i++)
	{
		for (int j=std::abs(i) - max_atk; j<=max_atk - std::abs(i);j++)
		{
			int pos = get_unit_array_pos(current_player_->get_x()+i*globals.TILE_SIZE,current_player_->get_y()+j*globals.TILE_SIZE);
			if (pos >= 0 && character_map_[pos] && !character_map_[pos]->is_player())
			{
				return true;
			}
		}
	}
	return false;

}

/************************* UPDATING POSITION/END OF TURN METHODS **************************/

void Game::update_enemy_positions()
{
	for (auto it = enemy_vector_.begin(); it != enemy_vector_.end(); ++it)
	{
		scene_.impassable_terrain_[get_unit_array_pos((*it)->get_x(), (*it)->get_y())] = 1;
		character_map_[get_unit_array_pos((*it)->get_x(), (*it)->get_y())] = (*it).get();
	}
}

void Game::update_player_positions()
{
	for (auto it = player_vector_.begin(); it != player_vector_.end(); ++it)
	{
		character_map_[get_unit_array_pos((*it)->get_x(),(*it)->get_y())] = (*it).get();
	}
}

void Game::unit_is_done(const std::shared_ptr<Character>& unit)
{
	unit->set_state(Character::idle);
	unit->set_grey(true);
	character_map_[get_unit_array_pos(unit->get_old_x(),unit->get_old_y())] = nullptr;
	character_map_[get_unit_array_pos(unit->get_x(),unit->get_y())] = unit.get();
	if (unit->is_player())
	{
		if (--active_players_ == 0)
		{
			game_state_ = enemy_move;
			active_enemies_ = enemy_vector_.size();
		}
	}
	else
	{
		if (--active_enemies_ == 0)
		{
			game_state_ = none;
			active_players_ = player_vector_.size();
			reset_camera(mc_); // reset to MC actually
		}
	}
}


/************************* HELPER METHODS **************************/

int Game::get_unit_array_pos(const int x, const int y)
{
	return y/globals.TILE_SIZE*scene_.get_level_map_width_tiles()+x/globals.TILE_SIZE;
}

void Game::draw_characters()
{
	for (auto it = player_vector_.begin(); it != player_vector_.end(); ++it)
	{
		(*it)->draw(camera_, renderer_);
	}
	for (auto it = enemy_vector_.begin(); it != enemy_vector_.end(); ++it)
	{
		(*it)->draw(camera_, renderer_);
	}
}

void Game::create_players()
{
	std::shared_ptr<Character> cur(new Character("Seth",Character::cavalier,0,0,true,Stats(20,10,10,10,10)));

	// give weapons and items

	// add player to vector
	player_vector_.push_back(cur);
	// set mc
	mc_ = cur;

	// add more players
	
	active_players_ = player_vector_.size();

	// load enemies
	cur.reset(new Character("Enemy",Character::swordsman,0,globals.TILE_SIZE,false,Stats(20,10,10,10,10)));
	// give enemy weapon(s)

	enemy_vector_.push_back(cur);

}