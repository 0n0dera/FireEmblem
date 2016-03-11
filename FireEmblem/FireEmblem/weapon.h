#pragma once
#include "item.h"
#include "weapon_stats.h"

class Character;

class Weapon : public Item
{
public:
	enum WeaponType {
		sword = 1,
		lance = 2,
		axe = 4,
		bow = 8,
		magic = 16,
		heal = 32
	};

	Weapon(std::string name, WeaponType type);
	~Weapon(void);
	int get_max_attack_range() const;
	int get_min_attack_range() const;
	void use(const std::shared_ptr<Character> unit) override;
	WeaponType get_type() const;

private:
	std::string name_;
	WeaponType type_;
	WeaponStats stats_;
};

inline int Weapon::get_max_attack_range() const
{
	return stats_.max_range_;
}
inline int Weapon::get_min_attack_range() const
{
	return stats_.min_range_;
}
inline Weapon::WeaponType Weapon::get_type() const
{
	return type_;
}