#pragma once
class CharacterData
{
public:
	~CharacterData(void);
	const static std::vector<int> equippable_weapons_vector_;
	const static std::vector<int> steps_vector_;
private:
	CharacterData(void);
	static std::vector<int> create_steps_vector();
	static std::vector<int> create_equippable_weapons_vector();
};

