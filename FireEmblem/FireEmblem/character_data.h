#pragma once
#include "stats.h"

class CharacterData
{
public:
	~CharacterData(void);
	static const std::vector<int>& get_equippable_weapons_vector();
	static const std::vector<int>& get_steps_vector();
	static const std::map<std::string,Stats>& get_stats_map();
private:
	CharacterData(void);
	
	static std::vector<int> create_equippable_weapons_vector();
	static std::vector<int> create_steps_vector();
	static std::map<std::string,Stats> create_stats_map();
};

