#include "stdafx.h"
#include "current_tile.h"

CurrentTile::CurrentTile():actual_x_(0),actual_y_(0),frame_(0)
{
}

CurrentTile::~CurrentTile(){};

void CurrentTile::inc_frame()
{
	static bool inc = true;
	if (frame_ == 5) inc = false;
	else if (frame_ == 0) inc = true;

	if (inc) frame_++;
	else frame_--;
}