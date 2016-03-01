#pragma once

class SpriteSheet
{
private:
	SpriteSheet(); // static class
	const static std::string PLAYER_SPRITE_FILE_PATH;
	const static std::string ENEMY_SPRITE_FILE_PATH;

public:
	static SDL_Texture* player_sprites;
	static SDL_Texture* enemy_sprites;
	static void init_sprites(SDL_Renderer* renderer);
	~SpriteSheet();
};

