#include "stdafx.h"
#include "potion.h"
#include "item.h"
#include "character.h"

Potion::Potion(int heal):heal_(heal)
{
}


Potion::~Potion(void)
{
}

void Potion::use(const std::shared_ptr<Character> unit)
{
	unit->set_hp(std::min(unit->get_max_hp(),unit->get_hp()+heal_));
}