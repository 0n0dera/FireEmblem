#pragma once
#include "character.h"

class Swordsman :
	public Character
{
public:
	Swordsman(std::string name, bool mc, int x, int y, bool is_player, Stats stats);
	~Swordsman(void);
	void set_weapon(Weapon* const weapon) override;
};

