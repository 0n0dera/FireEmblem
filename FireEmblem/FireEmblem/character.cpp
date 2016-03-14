#include "stdafx.h"
#include "character.h"
#include "sprite_sheet.h"
#include "potion.h"
#include "character_data.h"
#include "weapon.h"

Character::Character(std::string name, CharacterClass c_class, int x, int y, bool is_player): 
	name_(name),
	class_(c_class),
	x_(x),
	y_(y), 
	old_x_(x),
	old_y_(y),
	state_(idle), 
	frame_(0),
	anim_delay_(100), 
	last_anim_frame_time_(0), 
	num_steps_(CharacterData::get_steps_vector().at(c_class)), 
	is_player_(is_player), 
	sprite_y_start_(SpriteSheet::get_unit_y_start_map().at(name)), 
	grey_(false),
	can_act_(true),
	can_attack_(false),
	stats_(CharacterData::get_stats_map().at(name)),
	null_ptr(std::shared_ptr<Weapon>()),
	cur_weapon_(null_ptr),
	weapon_list_(std::vector<std::shared_ptr<Weapon>>()),
	inventory_(std::vector<std::shared_ptr<Item>>()),
	equippable_weapon_mask_(CharacterData::get_equippable_weapons_vector().at(c_class))
{
}

Character::~Character()
{
};

int Character::get_max_attack_range() const
{
	if (cur_weapon_ == null_ptr) return 0;
	return cur_weapon_->get_max_attack_range();
}

int Character::get_min_attack_range() const
{
	if (cur_weapon_ == null_ptr) return 0;
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

bool Character::attack(const std::shared_ptr<Character>& enemy)
{
	// do dmg calcs
	return false;
}

bool Character::can_equip(const std::shared_ptr<const Weapon>& weapon)
{
	return ((weapon->get_type() & equippable_weapon_mask_) != 0);
}

void Character::set_weapon(const std::shared_ptr<Weapon>& weapon)
{
	if (can_equip(weapon))
	{
		cur_weapon_ = weapon;
	}
}

void Character::give_weapon(const std::shared_ptr<Weapon>& weapon)
{
	weapon_list_.push_back(weapon);
	inventory_.push_back(weapon);
}

void Character::give_item(const std::shared_ptr<Item>& item)
{
	inventory_.push_back(item);
}