#pragma once

class SpriteSheet
{

public:
	const static int kPlayerSpriteStartX = Globals::SPRITE_SIZE * 4;
	const static int kEnemySpriteStartX = 0;
	const static int kAnimationFrames = 4;

	~SpriteSheet();
	static void init_sprites(SDL_Renderer* renderer);
	
	static SDL_Texture* player_sprites_;
	static SDL_Texture* enemy_sprites_;

private:
	const static std::string kPlayerSpriteFilePath;
	const static std::string kEnemySpriteFilePath;

	SpriteSheet(); // static class
	
};

