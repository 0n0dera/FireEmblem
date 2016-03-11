#include "stdafx.h"
#include "mage.h"


Mage::Mage(std::string name, bool mc, int x, int y, bool is_player, Stats stats): Character(name,mc,x,y,4,1,1,is_player,false,4*globals.ROWS_PER_CLASS*globals.SPRITE_SIZE,stats)
{
}


Mage::~Mage(void)
{
}