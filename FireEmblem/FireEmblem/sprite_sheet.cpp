#include "stdafx.h"
#include "sprite_sheet.h"

const std::string SpriteSheet::kPlayerSpriteFilePath = "Textures/player_sprites.png";
const std::string SpriteSheet::kEnemySpriteFilePath = "Textures/enemy_sprites.png";

const std::map<std::string,int> SpriteSheet::unit_y_start_map = SpriteSheet::create_map();

SDL_Texture* SpriteSheet::player_sprites_ = NULL;
SDL_Texture* SpriteSheet::enemy_sprites_ = NULL;

void SpriteSheet::init_sprites(SDL_Renderer* renderer)
{
	texture::load_texture_from_file(kPlayerSpriteFilePath, player_sprites_, renderer);
	texture::load_texture_from_file(kEnemySpriteFilePath, enemy_sprites_, renderer);
}

std::map<std::string,int> SpriteSheet::create_map()
{
	std::map<std::string,int> m;
	// m["Erikia"] = 0;
	return m;
}

SpriteSheet::~SpriteSheet()
{
	SDL_DestroyTexture(player_sprites_);
	SDL_DestroyTexture(enemy_sprites_);
}
