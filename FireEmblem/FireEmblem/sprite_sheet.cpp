#include "stdafx.h"
#include "sprite_sheet.h"

const std::string SpriteSheet::PLAYER_SPRITE_FILE_PATH = "Textures/player_sprites.png";
const std::string SpriteSheet::ENEMY_SPRITE_FILE_PATH =  "Texture/enemy_sprites.png";

SDL_Texture* SpriteSheet::player_sprites = NULL;
SDL_Texture* SpriteSheet::enemy_sprites = NULL;

void SpriteSheet::init_sprites(SDL_Renderer* renderer)
{
	texture::load_texture_from_file(PLAYER_SPRITE_FILE_PATH, player_sprites, renderer);
	texture::load_texture_from_file(ENEMY_SPRITE_FILE_PATH, enemy_sprites, renderer);
}

SpriteSheet::~SpriteSheet()
{
	SDL_DestroyTexture(player_sprites);
	SDL_DestroyTexture(enemy_sprites);
}
