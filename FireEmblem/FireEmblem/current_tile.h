#pragma once
class CurrentTile
{
public:
	CurrentTile();
	~CurrentTile();
	int get_actual_x() const;
	int get_actual_y() const;
	void inc_actual_x(int amount);
	void inc_actual_y(int amount);
	void set_actual_x(int x);
	void set_actual_y(int y);
	void inc_frame();
	int get_frame() const;

private:
	int frame_;
	int actual_x_;
	int actual_y_;
};

inline int CurrentTile::get_actual_x() const
{
	return actual_x_;
}

inline int CurrentTile::get_actual_y() const
{
	return actual_y_;
}
inline void CurrentTile::inc_actual_x(int amount)
{
	actual_x_ += amount;
}

inline void CurrentTile::inc_actual_y(int amount)
{
	actual_y_ += amount;
}

inline void CurrentTile::set_actual_x(int x)
{
	actual_x_ = x;
}

inline void CurrentTile::set_actual_y(int y)
{
	actual_y_ = y;
}

inline int CurrentTile::get_frame() const
{
	return frame_;
}