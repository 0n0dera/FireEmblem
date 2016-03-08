#pragma once
class Camera
{
public:
	Camera(void);
	~Camera(void);
	int get_camera_x() const;
	int get_camera_y() const;
	void inc_camera_x();
	void inc_camera_y();
	void dec_camera_x();
	void dec_camera_y();
	void set_camera_x(int x);
	void set_camera_y(int y);
	int get_camera_x_bound() const;
	int get_camera_y_bound() const;

private:
	int camera_x_;
	int camera_y_;
};

inline int Camera::get_camera_x() const
{
	return camera_x_;
}

inline int Camera::get_camera_y() const
{
	return camera_y_;
}

inline void Camera::inc_camera_x()
{
	camera_x_ += Globals::TILE_SIZE;
}

inline void Camera::inc_camera_y()
{
	camera_y_ += Globals::TILE_SIZE;
}

inline void Camera::dec_camera_x()
{
	camera_x_ -= Globals::TILE_SIZE;
}

inline void Camera::dec_camera_y()
{
	camera_y_ -= Globals::TILE_SIZE;
}

inline void Camera::set_camera_x(int amount)
{
	camera_x_ = amount;
}

inline void Camera::set_camera_y(int amount)
{
	camera_y_ = amount;
}

inline int Camera::get_camera_x_bound() const
{
	return camera_x_ + Globals::SCREEN_WIDTH;
}

inline int Camera::get_camera_y_bound() const
{
	return camera_y_ + Globals::SCREEN_HEIGHT;
}