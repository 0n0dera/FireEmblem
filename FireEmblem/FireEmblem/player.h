#pragma once
#include "character.h"

class Player: public Character
{
public:
	Player(int x, int y);
	~Player();
	void draw(const Camera& camera, SDL_Renderer* renderer) override;
	void move() override;

private:
	
};

