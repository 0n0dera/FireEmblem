#include "stdafx.h"
#include "weapon_stats.h"


WeaponStats::WeaponStats(int dmg, int minr, int maxr):
	dmg_(dmg),
	max_range_(maxr),
	min_range_(minr)
{
}


WeaponStats::~WeaponStats(void)
{
}
