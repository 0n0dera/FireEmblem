#pragma once
#include "camera.h"
#include "stats.h"
#include "Items\Weapons\weapon.h"
#include "Items\item.h"

class Potion;

class Character
{

public:
	enum CharacterState { 
		idle = 0, 
		selected = 4, 
		move_up = 5, 
		move_right = 3, 
		move_down = 4,
		move_left = 2,
		attacking = 1
	};
	Character(std::string name, bool is_mc, int x, int y, int num_steps, bool is_player, bool is_healer, Stats stats);
	virtual ~Character(void) = 0;

	std::string get_name() const;

	// position methods
	int get_x() const;
	int get_y() const;
	int get_old_x() const;
	int get_old_y() const;
	int get_tex_x() const;
	int get_tex_y() const;
	void set_x(int new_x);
	void set_y(int new_y);
	void set_old_x(int new_x);
	void set_old_y(int new_y);

	// draw method to override
	void draw(const Camera& camera, SDL_Renderer* renderer);

	// move methods
	void move();
	int get_frame() const;
	int get_state() const;
	void set_state(CharacterState state);
	int get_num_steps() const;
	int get_max_attack_range() const;
	int get_min_attack_range() const;

	int get_sprite_y_start() const;
	bool is_player() const;
	bool is_grey() const;
	void set_grey(bool val);
	bool can_act() const;
	void set_act(bool val);
	bool is_healer() const; // this is bad
	bool is_mc() const;

	// stats methods
	int get_hp() const;
	int get_max_hp() const;
	int get_atk() const;
	int get_def() const;
	int get_spd() const;
	int get_luk() const;
	void set_hp(int hp);

	// weapon/item methods
	virtual void set_weapon(Weapon* const weapon) = 0;
	void give_weapon(Weapon* const weapon);
	void give_item(Item* const item);

	// attack
	virtual bool attack(Character* const enemy);


private:
	
	// animation methods
	int get_anim_delay() const;
	void count_anim_delay();
	void inc_frame();
	
	const std::string name_;
	
	int x_;
	int y_;
	int old_x_;
	int old_y_;

	// animation variables
	int anim_delay_;
	int last_anim_frame_time_;
	int frame_;
	CharacterState state_;
	int sprite_y_start_;

	int num_steps_;
	
	bool is_player_;
	bool grey_;
	bool can_act_;
	bool is_healer_; // this is bad
	bool is_mc_;

	//stats
	Stats stats_;

	// items
	Weapon* cur_weapon_;
	std::vector<Weapon*> weapon_list_;
	std::vector<Item*> inventory_;

};


inline int Character::get_x() const
{
	return x_;
}
inline int Character::get_y() const
{
	return y_;
}
inline int Character::get_old_x() const
{
	return old_x_;
}
inline int Character::get_old_y() const
{
	return old_y_;
}
inline int Character::get_tex_x() const
{
	return x_;
}
inline int Character::get_tex_y() const
{
	return y_ + globals.TILE_SIZE;
}
inline void Character::set_x(int new_x)
{
	x_ = new_x;
}
inline void Character::set_y(int new_y)
{
	y_ = new_y;
}
inline void Character::set_old_x(int new_x)
{
	old_x_ = new_x;
}
inline void Character::set_old_y(int new_y)
{
	old_y_ = new_y;
}
inline int Character::get_frame() const
{
	return frame_;
}

inline int Character::get_state() const
{
	return state_;
}

inline void Character::set_state(CharacterState state)
{
	state_ = state;
}

inline int Character::get_anim_delay() const
{
	return anim_delay_;
}

inline int Character::get_num_steps() const
{
	return num_steps_;
}

inline int Character::get_sprite_y_start() const
{
	return sprite_y_start_;
}

inline bool Character::is_grey() const
{
	return grey_;
}

inline void Character::set_grey(bool val)
{
	grey_ = val;
}
inline bool Character::is_player() const
{
	return is_player_;
}
inline bool Character::can_act() const
{
	return can_act_;
}
inline void Character::set_act(bool val)
{
	can_act_ = val;
}
inline bool Character::is_healer() const
{
	return is_healer_;
}
inline int Character::get_hp() const
{
	return stats_.hp_;
}
inline int Character::get_max_hp() const
{
	return stats_.max_hp_;
}
inline int Character::get_atk() const
{
	return stats_.atk_;
}
inline int Character::get_def() const
{
	return stats_.def_;
}
inline int Character::get_spd() const
{
	return stats_.spd_;
}

inline int Character::get_luk() const
{
	return stats_.luk_;
}
inline std::string Character::get_name() const
{
	return name_;
}
inline bool Character::is_mc() const
{
	return is_mc_;
}