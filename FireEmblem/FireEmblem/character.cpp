#include "stdafx.h"
#include "character.h"
#include "sprite_sheet.h"
#include "potion.h"
#include "character_data.h"
#include "weapon.h"

Character::Character(std::string name, CharacterClass c_class, int x, int y, bool is_player, Stats stats): 
	name_(name),class_(c_class),x_(x), y_(y), old_x_(x),old_y_(y),state_(idle), frame_(0), anim_delay_(100), last_anim_frame_time_(0), num_steps_(CharacterData::steps_vector_[c_class]), is_player_(is_player), 
	sprite_y_start_(SpriteSheet::unit_y_start_map.at(name)), grey_(false),can_act_(true),stats_(stats),
	cur_weapon_(std::shared_ptr<Weapon>()),weapon_list_(std::vector<std::shared_ptr<Weapon>>()),inventory_(std::vector<std::shared_ptr<Item>>()),equippable_weapon_mask_(CharacterData::equippable_weapons_vector_.at(c_class))
{
}

Character::~Character()
{
};

int Character::get_max_attack_range() const
{
	return cur_weapon_->get_max_attack_range();
}

int Character::get_min_attack_range() const
{
	return cur_weapon_->get_min_attack_range();
}

void Character::count_anim_delay()
{
	int cur_anim_frame_time = SDL_GetTicks();
	if (cur_anim_frame_time - last_anim_frame_time_ > anim_delay_)
	{
		last_anim_frame_time_ = cur_anim_frame_time;
		inc_frame();
	}
}

void Character::inc_frame()
{
	++frame_ %= SpriteSheet::kAnimationFrames;
}

void Character::move()
{
	switch (state_)
	{
		case Character::move_up:
			set_y(get_y() - Globals::SPRITE_MOVE_SPEED);
			break;
		case Character::move_right:
			set_x(get_x() + Globals::SPRITE_MOVE_SPEED);
			break;
		case Character::move_down:
			set_y(get_y() + Globals::SPRITE_MOVE_SPEED);
			break;
		case Character::move_left:
			set_x(get_x() - Globals::SPRITE_MOVE_SPEED);
			break;
	}
}

void Character::draw(const Camera& camera, SDL_Renderer* renderer)
{
	count_anim_delay();
	int sprite_start_x;
	if (is_player_)
	{
		sprite_start_x = SpriteSheet::kPlayerSpriteStartX;
	}
	else
	{
		sprite_start_x = SpriteSheet::kEnemySpriteStartX;
	}
	SDL_Rect dest_rect = { get_tex_x() - camera.get_camera_x(), get_tex_y() - globals.SPRITE_SIZE - camera.get_camera_y(), globals.SPRITE_SIZE, globals.SPRITE_SIZE };
	SDL_Rect src_rect = { sprite_start_x + get_frame()*globals.SPRITE_SIZE, get_sprite_y_start() + get_state()*globals.SPRITE_SIZE, globals.SPRITE_SIZE, globals.SPRITE_SIZE };

	SDL_RenderCopy(renderer, SpriteSheet::player_sprites_, &src_rect, &dest_rect);
}

bool Character::attack(const std::shared_ptr<Character> enemy)
{
	// do dmg calcs
	return false;
}

bool Character::can_equip(const Weapon* const weapon)
{
	return ((weapon->get_type() & equippable_weapon_mask_) != 0);
}

void Character::set_weapon(Weapon* const weapon)
{
	if (can_equip(weapon))
	{
		cur_weapon_.reset(weapon);
	}
}

void Character::give_weapon(const std::shared_ptr<Weapon> weapon)
{
	weapon_list_.push_back(weapon);
	inventory_.push_back(weapon);
}

void Character::give_item(const std::shared_ptr<Item> item)
{
	inventory_.push_back(item);
}