#pragma once
#include "Items\item.h"

class Character;

class Weapon : public Item
{
public:
	Weapon(int dmg, int crit, int max_range, int min_range, int durability);
	virtual ~Weapon(void) = 0;
	int get_max_attack_range() const;
	int get_min_attack_range() const;
	void use(Character* const unit) override;

private:
	int dmg_;
	int crit_;
	int max_attack_range_;
	int min_attack_range_;
	int durability_;
};

inline int Weapon::get_max_attack_range() const
{
	return max_attack_range_;
}
inline int Weapon::get_min_attack_range() const
{
	return min_attack_range_;
}
