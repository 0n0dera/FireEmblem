#pragma once
#include "camera.h"	

class Character
{

public:
	enum CharacterState { idle = 0, selected = 4, move_up = 5, move_right = 3, move_down = 4, move_left = 2, attacking = 1 };
	Character(int x, int y);
	virtual ~Character(void) = 0;
	int get_x() const;
	int get_y() const;
	int get_tex_x() const;
	int get_tex_y() const;
	void set_x(int new_x);
	void set_y(int new_y);
	virtual void draw(const Camera& camera, SDL_Renderer* renderer) = 0;
	virtual void move() = 0;
	void count_anim_delay();
	void inc_frame();
	int get_frame() const;
	int get_state() const;
	void set_state(CharacterState state);
	int get_anim_delay() const;

	int last_anim_frame_time_;

private:

	int x_;
	int y_;
	int frame_;
	int anim_delay_;

	CharacterState state_;
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