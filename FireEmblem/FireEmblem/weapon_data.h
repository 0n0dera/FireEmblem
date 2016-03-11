#pragma once
struct WeaponStats;
class WeaponData
{
public:
	~WeaponData(void);
	const static std::map<std::string,WeaponStats> weapon_stats_map_;
private:
	WeaponData(void);
	static std::map<std::string, WeaponStats> create_map();
};

