#include "stdafx.h"
#include "swordsman.h"


Swordsman::Swordsman(int x, int y, bool is_player): Character(x*globals.TILE_SIZE,y*globals.TILE_SIZE,4,1,1,is_player,0)
{
}


Swordsman::~Swordsman(void)
{
}

