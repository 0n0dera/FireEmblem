#pragma once
#include "character.h"

class Archer :
	public Character
{
public:
	Archer(std::string name, bool mc, int x, int y, bool is_player, Stats stats);
	~Archer(void);
};

