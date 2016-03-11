#pragma once
class Item
{
public:
	Item(void);
	virtual ~Item(void)=0;
	virtual void use(Character* const unit) = 0;
};

