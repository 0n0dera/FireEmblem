#pragma once
struct WeaponStats;
class WeaponData
{
public:
	~WeaponData(void);
	const static std::map<std::string,WeaponStats>& get_weapon_stats_map();
private:
	WeaponData(void);
	static std::map<std::string, WeaponStats> create_weapon_stats_map();
};

