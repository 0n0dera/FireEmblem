#pragma once

class Sprite
{
public:
	Sprite();
	~Sprite();
	static SDL_Surface* load(char* file_path);
	static bool draw()
};

