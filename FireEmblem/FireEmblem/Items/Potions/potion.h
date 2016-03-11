#pragma once

class Character;
class Potion: public Item
{
public:
	Potion(int heal);
	virtual ~Potion(void)=0;
	void use(Character* const unit) override;
	int get_heal() const; // may or may not be used
private:
	int heal_;
};

inline int Potion::get_heal() const
{
	return heal_;
}
