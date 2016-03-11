#pragma once

class Character;

class Item
{
public:
	Item(void);
	virtual ~Item(void)=0;
	virtual void use(const std::shared_ptr<Character> unit) = 0;
};

