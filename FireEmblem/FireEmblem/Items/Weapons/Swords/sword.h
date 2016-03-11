#pragma once
#include "../weapon.h"
class Sword :
	public Weapon
{
public:
	Sword(void);
	virtual ~Sword(void) = 0;
};

