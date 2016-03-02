#pragma once
#include "character.h"

class Swordsman :
	public Character
{
public:
	Swordsman(int x, int y, bool is_player);
	~Swordsman(void);
};

