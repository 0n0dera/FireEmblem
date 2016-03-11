#include "stdafx.h"
#include "archer.h"

class Swordsman;
class Mage;

Archer::Archer(std::string name, bool mc, int x, int y, bool is_player, Stats stats):Character(name, mc,x,y,4,1,1,is_player,false,2*globals.ROWS_PER_CLASS*globals.SPRITE_SIZE,stats)
{
}


Archer::~Archer(void)
{
}
