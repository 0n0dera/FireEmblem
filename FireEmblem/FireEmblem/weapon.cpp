#include "stdafx.h"
#include "weapon.h"
#include "item.h"
#include "character.h"
#include "weapon_stats.h"
#include "weapon_data.h"

Weapon::Weapon(std::string name, WeaponType type):
	name_(name),type_(type),stats_(WeaponData::weapon_stats_map_.at(name))
{
}


Weapon::~Weapon(void)
{
}

void Weapon::use(const std::shared_ptr<Character> unit)
{
	unit->set_weapon(this);
}