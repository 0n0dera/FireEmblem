#pragma once
struct Stats
{
	Stats(int hp, int atk, int def, int spd, int luk);
	~Stats(void);
	const int max_hp_;
	int hp_;
	int atk_;
	int def_;
	int spd_;
	int luk_;
};

