#include "stdafx.h"
#include "character.h"
#include "sprite_sheet.h"

Character::Character(int x, int y, int num_steps, int min_attack_range,int max_attack_range, bool is_player, int y_start): x_(x), y_(y), state_(idle), frame_(0), anim_delay_(100), last_anim_frame_time_(0), num_steps_(num_steps), max_attack_range_(max_attack_range), min_attack_range_(min_attack_range),is_player_(is_player), sprite_y_start_(y_start), turn_done_(false)
{
}

Character::~Character() {};

void Character::count_anim_delay()
{
	int cur_anim_frame_time = SDL_GetTicks();
	if (cur_anim_frame_time - last_anim_frame_time_ > 300)
	{
		last_anim_frame_time_ = cur_anim_frame_time;
		inc_frame();
	}
}

void Character::inc_frame()
{
	++frame_ %= SpriteSheet::kAnimationFrames;
}

void Character::move()
{
	switch (state_)
	{
		case Character::move_up:
			set_y(get_y() - globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_right:
			set_x(get_x() + globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_down:
			set_y(get_y() + globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_left:
			set_x(get_x() - globals.SPRITE_MOVE_SPEED);
			break;
	}
}

void Character::draw(const Camera& camera, SDL_Renderer* renderer)
{
	count_anim_delay();
	int sprite_start_x;
	if (is_player_)
	{
		sprite_start_x = SpriteSheet::kPlayerSpriteStartX;
	}
	else
	{
		sprite_start_x = SpriteSheet::kEnemySpriteStartX;
	}
	SDL_Rect dest_rect = { get_tex_x() - camera.get_camera_x(), get_tex_y() - globals.SPRITE_SIZE - camera.get_camera_y(), globals.SPRITE_SIZE, globals.SPRITE_SIZE };
	SDL_Rect src_rect = { sprite_start_x + get_frame()*globals.SPRITE_SIZE, get_sprite_y_start() + get_state()*globals.SPRITE_SIZE, globals.SPRITE_SIZE, globals.SPRITE_SIZE };
	SDL_RenderCopy(renderer, SpriteSheet::player_sprites_, &src_rect, &dest_rect);
}