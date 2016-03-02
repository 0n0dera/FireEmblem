#include "stdafx.h"
#include "character.h"
#include "sprite_sheet.h"

Character::Character(int x, int y): x_(x), y_(y), state_(idle), frame_(0), anim_delay_(100), last_anim_frame_time_(0)
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
