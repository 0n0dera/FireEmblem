#include "stdafx.h"
#include "character_data.h"
#include "character.h"
#include "stats.h"
#include "weapon.h"

CharacterData::CharacterData(void)
{
}


CharacterData::~CharacterData(void)
{
}

// create methods

std::vector<int> CharacterData::create_equippable_weapons_vector()
{
	std::vector<int> v(6);
	v[Character::cavalier] = Weapon::lance | Weapon::sword;
	v[Character::archer] = Weapon::bow;
	v[Character::swordsman] = Weapon::sword;
	v[Character::mage] = Weapon::magic;
	v[Character::axeman] = Weapon::axe;
	v[Character::healer] = Weapon::heal;
	return v;
}

std::vector<int> CharacterData::create_steps_vector()
{
	std::vector<int> v(6);
	v[Character::cavalier] = 8;
	v[Character::archer] = 6;
	v[Character::swordsman] = 5;
	v[Character::mage] = 5;
	v[Character::axeman] = 4;
	v[Character::healer] = 5;
	return v;
}

std::map<std::string, Stats> CharacterData::create_stats_map()
{
	std::map<std::string,Stats> m;
	m.insert(std::make_pair("Eirika",Stats(20,10,10,10,10)));
	return m;
}

// get methods

const std::vector<int>& CharacterData::get_equippable_weapons_vector()
{
	static std::vector<int> v = CharacterData::create_equippable_weapons_vector();
	return v;
}

const std::vector<int>& CharacterData::get_steps_vector()
{
	static std::vector<int> v = CharacterData::create_steps_vector();
	return v;
}

const std::map<std::string,Stats>& CharacterData::get_stats_map()
{
	static std::map<std::string,Stats> m = CharacterData::create_stats_map();
	return m;
}
