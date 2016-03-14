#pragma once
#include "item.h"

class Character;
class Potion: public Item
{
public:
	Potion(int heal);
	~Potion(void);
	void use(const std::shared_ptr<Character>& unit) override;
	int get_heal() const; // may or may not be used
private:
	int heal_;
};

inline int Potion::get_heal() const
{
	return heal_;
}
