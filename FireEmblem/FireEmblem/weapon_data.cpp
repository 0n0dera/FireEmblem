#include "stdafx.h"
#include "weapon_data.h"
#include "weapon_stats.h"


const std::map<std::string,WeaponStats> WeaponData::weapon_stats_map_ = WeaponData::create_map();

WeaponData::WeaponData(void)
{
}


WeaponData::~WeaponData(void)
{
}

std::map<std::string,WeaponStats> WeaponData::create_map()
{
	std::map<std::string,WeaponStats> m;
	// m["Erikia"] = 0;
	return m;
}