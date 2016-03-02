#pragma once
typedef struct
{
	static const int TILE_SIZE = 40;
	static const int SPRITE_SIZE = 43;
    static const int SCREEN_WIDTH = 400;
	static const int SCREEN_HEIGHT = 400;
	static const int TICKS_PER_SECOND = 25;
	static const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	static const int MAX_FRAMESKIP = 5;
	static const int SPRITE_MOVE_SPEED = 10;
} Globals;

extern Globals globals;