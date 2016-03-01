#pragma once
class CurrentTile
{
public:
	CurrentTile();
	~CurrentTile();
	int get_screen_x() const;
	int get_screen_y() const;
	int get_actual_x() const;
	int get_actual_y() const;
	void inc_screen_x(int amount);
	void inc_screen_y(int amount);
	void inc_actual_x(int amount);
	void inc_actual_y(int amount);	
	void set_screen_x(int x);
	void set_screen_y(int y);
	void set_actual_x(int x);
	void set_actual_y(int y);

private:
	int screen_x_;
	int screen_y_;
	int actual_x_;
	int actual_y_;
};

inline int CurrentTile::get_screen_x() const
{
	return screen_x_;
}

inline int CurrentTile::get_screen_y() const
{
	return screen_y_;
}

inline int CurrentTile::get_actual_x() const
{
	return actual_x_;
}

inline int CurrentTile::get_actual_y() const
{
	return actual_y_;
}

inline void CurrentTile::inc_screen_x(int amount)
{
	screen_x_ += amount;
}

inline void CurrentTile::inc_screen_y(int amount)
{
	screen_y_ += amount;
}

inline void CurrentTile::inc_actual_x(int amount)
{
	actual_x_ += amount;
}

inline void CurrentTile::inc_actual_y(int amount)
{
	actual_y_ += amount;
}

inline void CurrentTile::set_screen_x(int x)
{
	screen_x_ = x;
}

inline void CurrentTile::set_screen_y(int y)
{
	screen_y_ = y;
}

inline void CurrentTile::set_actual_x(int x)
{
	actual_x_ = x;
}

inline void CurrentTile::set_actual_y(int y)
{
	actual_y_ = y;
}