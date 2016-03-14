#include "stdafx.h"
#include "player_menu.h"
#include "scene.h"
#include "character.h"

PlayerMenu::PlayerMenu(void):
	selection_(0),
	left_side_(20),
	right_side_(globals.SCREEN_WIDTH-120),
	menu_width_(100),
	menu_y_(20),
	item_height_(30),
	const_num_options_(3),
	can_act_(false),
	can_attack_(false),
	options_vector_(std::vector<MenuSelection>())
{
}


PlayerMenu::~PlayerMenu(void)
{
}

void PlayerMenu::draw(bool left_side, const Scene& scene, SDL_Renderer* renderer)
{
	if (left_side)
	{
		draw_menu(left_side_, renderer);
	}
	else
	{
		draw_menu(right_side_, renderer);
	}
}


void PlayerMenu::draw_menu(const int x, SDL_Renderer* renderer)
{
	SDL_Rect rect = {x, menu_y_,menu_width_,10};
	SDL_SetRenderDrawColor(renderer, 50,50,50,255);
	SDL_RenderFillRect(renderer, &rect);
	rect.h = item_height_;
	int num_opts = 0;

	for (const auto& option : options_vector_)
	{
		rect.y = menu_y_ + 10 + num_opts++*item_height_;
		
		if (option == MenuSelection::attack)
		{
			// draw attack
			SDL_SetRenderDrawColor(renderer, 255,0,0,255);
			SDL_RenderFillRect(renderer,&rect);
		}
		else if (option == MenuSelection::heal)
		{
			// draw heal
		}
		else if (option == MenuSelection::item)
		{
			// draw item
			SDL_SetRenderDrawColor(renderer, 0,0,255,255);
			SDL_RenderFillRect(renderer,&rect);
		}
		else if (option == MenuSelection::wait)
		{	
			// draw wait
			SDL_SetRenderDrawColor(renderer, 0,0,0,255);
			SDL_RenderFillRect(renderer,&rect);
		}
	}

	// draw menu bottom
	rect.h = 10;
	SDL_SetRenderDrawColor(renderer, 50,50,50,255);
	SDL_RenderFillRect(renderer, &rect);

	// draw selector
	SDL_SetRenderDrawColor(renderer, 0, 255,255,255);
	rect.h = item_height_;
	rect.y = menu_y_ + 10 + item_height_*selection_;
	SDL_RenderDrawRect(renderer,&rect);

}

void PlayerMenu::inc_selection(int inc)
{
	selection_ += inc;
	if (selection_ < 0) selection_ = options_vector_.size() - 1;
	selection_ = selection_ % options_vector_.size();
}

void PlayerMenu::set_options(const std::shared_ptr<const Character>& player)
{
	options_vector_.clear();
	can_attack_ = player->can_attack();
	can_act_ = player->can_act();
	// reset selection to 0
	selection_ = 0;
	if (can_act_)
	{
		if (can_attack_)
		{
			if (player->get_class() == Character::healer)
			{

				options_vector_.push_back(MenuSelection::heal);
			}
			else
			{
				options_vector_.push_back(MenuSelection::attack);
			} 
		}		
		options_vector_.push_back(MenuSelection::item);
	}
	options_vector_.push_back(MenuSelection::wait);
}

int PlayerMenu::get_selection() const
{
	return options_vector_.at(selection_);
}