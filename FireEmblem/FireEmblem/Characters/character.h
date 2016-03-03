#pragma once
#include "../camera.h"	

class Character
{

public:
	enum CharacterState { idle = 0, selected = 4, move_up = 5, move_right = 3, move_down = 4, move_left = 2, attacking = 1 };
	Character(int x, int y, int num_steps, int min_attack_range, int max_attack_range, bool is_player, int y_start);
	virtual ~Character(void) = 0;
	// getters and setters
	int get_x() const;
	int get_y() const;
	int get_tex_x() const;
	int get_tex_y() const;
	void set_x(int new_x);
	void set_y(int new_y);
	// draw method to override
	void draw(const Camera& camera, SDL_Renderer* renderer);
	void count_anim_delay();
	// move methods
	void move();
	int get_frame() const;
	int get_state() const;
	void set_state(CharacterState state);
	int get_anim_delay() const;
	int get_num_steps() const;
	int get_max_attack_range() const;
	int get_min_attack_range() const;
	int get_sprite_y_start() const;
	bool is_turn_done() const;
	void set_turn_done(bool val);

	int last_anim_frame_time_;

private:

	void inc_frame();

	int x_;
	int y_;
	int frame_;
	int anim_delay_;
	int num_steps_;
	int max_attack_range_;
	int min_attack_range_;
	CharacterState state_;
	bool is_player_;
	int sprite_y_start_;
	bool turn_done_;
};


inline int Character::get_x() const
{
	return x_;
}
inline int Character::get_y() const
{
	return y_;
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

inline int Character::get_max_attack_range() const
{
	return max_attack_range_;
}

inline int Character::get_min_attack_range() const
{
	return min_attack_range_;
}

inline int Character::get_sprite_y_start() const
{
	return sprite_y_start_;
}

inline bool Character::is_turn_done() const
{
	return turn_done_;
}

inline void Character::set_turn_done(bool val)
{
	turn_done_ = val;
}