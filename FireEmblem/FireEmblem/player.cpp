#include "stdafx.h"
#include "player.h"
#include "sprite_sheet.h"

Player::Player(int x, int y):Character(x,y)
{
}

Player::~Player()
{
}

void Player::draw(const Camera& camera, SDL_Renderer * renderer)
{
	count_anim_delay();
	SDL_Rect dest_rect = { get_tex_x() - camera.get_camera_x(), get_tex_y() - globals.SPRITE_SIZE - camera.get_camera_y(), globals.SPRITE_SIZE, globals.SPRITE_SIZE };
	SDL_Rect src_rect = { SpriteSheet::kPlayerSpriteStartX + get_frame()*globals.SPRITE_SIZE, get_state()*globals.SPRITE_SIZE, globals.SPRITE_SIZE, globals.SPRITE_SIZE };
	SDL_RenderCopy(renderer, SpriteSheet::player_sprites_, &src_rect, &dest_rect);
}

void Player::move()
{
	switch (get_state())
	{
		case Character::move_up:
			set_y(get_y() - globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_right:
			set_x(get_x() + globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_down:
			set_y(get_y() + globals.SPRITE_MOVE_SPEED);
			break;
		case Character::move_left:
			set_x(get_x() - globals.SPRITE_MOVE_SPEED);
			break;
	}
}