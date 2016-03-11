#include "stdafx.h"
#include "player_menu.h"
#include "scene.h"
#include "Characters\character.h"

PlayerMenu::PlayerMenu(void):selection_(0),left_side_(20),right_side_(globals.SCREEN_WIDTH-120),menu_width_(100),menu_y_(20),item_height_(30)
{
}


PlayerMenu::~PlayerMenu(void)
{
}

void PlayerMenu::draw(bool left_side, const Character* const player, const Scene& scene, SDL_Renderer* renderer)
{
	if (left_side)
	{
		draw_menu(left_side_, player, renderer);
	}
	else
	{
		draw_menu(right_side_, player, renderer);
	}
}


void PlayerMenu::draw_menu(const int x, const Character* const player, SDL_Renderer* renderer)
{
	SDL_Rect rect = {x, menu_y_,menu_width_,10};
	SDL_SetRenderDrawColor(renderer, 50,50,50,255);
	SDL_RenderFillRect(renderer, &rect);
	int num_opts = 0;

	if (player && player->can_act())
	{
		if (!player->is_healer())
		{
			// draw attack
			SDL_SetRenderDrawColor(renderer, 255,0,0,255);
			rect.y = menu_y_ + 10 + num_opts++*item_height_;
			rect.h = item_height_;
			SDL_RenderFillRect(renderer,&rect);
		}
		else
		{
			// draw heal
		}

		// draw item
		SDL_SetRenderDrawColor(renderer, 0,0,255,255);
		rect.y = menu_y_ + 10 + num_opts++*item_height_;
		SDL_RenderFillRect(renderer,&rect);
	}

	// draw wait
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	rect.y = menu_y_ + 10 + num_opts++*item_height_;
	SDL_RenderFillRect(renderer,&rect);

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
	if (selection_ < 0) selection_ = 2;
	selection_ = selection_ % 3;
}