#include "stdafx.h"
#include "weapon_data.h"
#include "weapon_stats.h"

WeaponData::WeaponData(void)
{
}


WeaponData::~WeaponData(void)
{
}

// create methods

std::map<std::string,WeaponStats> WeaponData::create_weapon_stats_map()
{
	std::map<std::string,WeaponStats> m;
	m.insert(std::make_pair("Iron Sword", WeaponStats(10,1,1)));
	return m;
}

// get methods

const std::map<std::string,WeaponStats>& WeaponData::get_weapon_stats_map()
{
	static std::map<std::string,WeaponStats> m = WeaponData::create_weapon_stats_map();
	return m;
}
