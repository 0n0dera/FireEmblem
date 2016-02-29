#pragma once

class SpriteSheet
{
private:
	const static std::string PLAYER_SPRITE_FILE_PATH;
	const static std::string ENEMY_SPRITE_FILE_PATH;

	SDL_Texture* player_sprites;
	SDL_Texture* enemy_sprites;

public:
	SpriteSheet(SDL_Renderer* renderer);
	~SpriteSheet();
};

