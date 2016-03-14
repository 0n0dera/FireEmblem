#include "stdafx.h"
#include "current_tile.h"

CurrentTile::CurrentTile():
	actual_x_(0),
	actual_y_(0), 
	frame_(0),
	anim_delay_(600), 
	frame_max_(10)
{
}

CurrentTile::~CurrentTile(){};

void CurrentTile::inc_frame()
{
	static bool inc = true;
	static int last_tick = 0;
	int current_tick = SDL_GetTicks();
	if (frame_ == frame_max_) frame_ = 6;
	if (frame_ == 6)
	{
		if (current_tick - last_tick > anim_delay_)
		{
			last_tick = current_tick;
		}
		else
		{
			return;
		}
		inc = false;
	}
	else if (frame_ == 0) inc = true;

	if (inc) frame_+=2;
	else frame_-=2;
}

void CurrentTile::set_frame_max()
{
	frame_ = frame_max_;
}
