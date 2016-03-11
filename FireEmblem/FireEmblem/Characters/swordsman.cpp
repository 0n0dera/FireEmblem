#include "stdafx.h"
#include "swordsman.h"
#include "stats.h"

Swordsman::Swordsman(std::string name, bool mc, int x, int y, bool is_player, Stats stats): Character(name,is_mc,x,y,4,1,1,is_player,false,0*globals.ROWS_PER_CLASS*globals.SPRITE_SIZE,stats)
{
}


Swordsman::~Swordsman(void)
{
}

void Swordsman::set_weapon(Weapon* const weapon)
{

}