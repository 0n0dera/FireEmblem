#include "stdafx.h"
#include "Potion.h"
#include "Items\item.h"
#include "Characters/character.h"

Potion::Potion(int heal):heal_(heal)
{
}


Potion::~Potion(void)
{
}

void Potion::use(Character* const unit)
{
	unit->set_hp(std::min(unit->get_max_hp(),unit->get_hp()+heal_));
}