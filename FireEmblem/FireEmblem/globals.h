#pragma once
typedef struct
{
	static const int TILE_SIZE = 30;
    static const int SCREEN_WIDTH = 450;
	static const int SCREEN_HEIGHT = 450;
	static const int TICKS_PER_SECOND = 25;
	static const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	static const int MAX_FRAMESKIP = 5;
} Globals;

extern Globals globals;