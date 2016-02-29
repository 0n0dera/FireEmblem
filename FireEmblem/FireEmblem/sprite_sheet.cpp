#include "stdafx.h"
#include "sprite_sheet.h"

const std::string PLAYER_SPRITE_FILE_PATH = "Textures/player_sprites.png";
const std::string ENEMY_SPRITE_FILE_PATH =  "Texture/enemy_sprites.png";


SpriteSheet::SpriteSheet(SDL_Renderer* renderer): player_sprites(NULL), enemy_sprites(NULL)
{
	texture::load_texture_from_file(PLAYER_SPRITE_FILE_PATH,player_sprites,renderer);
	texture::load_texture_from_file(ENEMY_SPRITE_FILE_PATH,enemy_sprites,renderer);
}