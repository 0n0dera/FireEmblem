#pragma once
class Character
{
public:
	Character(void);
	virtual ~Character(void) = 0;
	int get_x() const;
	int get_y() const;
	void set_x(int new_x);
	void set_y(int new_y);
	virtual void draw(SDL_Renderer* renderer) = 0;


private:
	enum CharacterState { idle, selected, moving, attacking };

	int x;
	int y;
	CharacterState state;
};


inline int Character::get_x() const
{
	return x;
}
inline int Character::get_y() const
{
	return y;
}
inline void Character::set_x(int new_x)
{
	x = new_x;
}
inline void Character::set_y(int new_y)
{
	y = new_y;
}