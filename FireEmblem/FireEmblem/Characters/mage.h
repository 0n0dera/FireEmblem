#pragma once
#include "character.h"
class Mage :
	public Character
{
public:
	Mage(std::string name, bool mc, int x, int y, bool is_player, Stats stats);
	~Mage(void);

	
};

