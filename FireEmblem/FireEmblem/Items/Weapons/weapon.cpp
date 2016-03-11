#include "stdafx.h"
#include "weapon.h"
#include "../item.h"
#include "../../Characters/character.h"

Weapon::Weapon(int dmg, int crit, int max_range, int min_range, int durability):
	dmg_(dmg),crit_(crit),max_attack_range_(max_range),min_attack_range_(min_range),durability_(durability)
{
}


Weapon::~Weapon(void)
{
}

void Weapon::use(Character* const unit)
{
	unit->set_weapon(this);
}