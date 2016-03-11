#pragma once
struct WeaponStats
{
	WeaponStats(int dmg,int maxr, int minr);
	~WeaponStats(void);
	int dmg_;
	int max_range_;
	int min_range_;
};

