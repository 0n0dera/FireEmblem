#include "stdafx.h"
#include "character_data.h"
#include "character.h"
#include "weapon.h"

const std::vector<int> CharacterData::steps_vector_ = CharacterData::create_steps_vector();
const std::vector<int> CharacterData::equippable_weapons_vector_ = CharacterData::create_equippable_weapons_vector();

CharacterData::CharacterData(void)
{
}


CharacterData::~CharacterData(void)
{
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