#pragma once
#include "camera.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);
	void draw_level_map(const Camera& camera, SDL_Renderer* renderer) const;
	void change_level_map(int level, SDL_Renderer* renderer);
	int get_level_map_height() const;
	int get_level_map_width() const;

private:
	static const std::string kCommonLevelMapPath;

	int level_map_height_;
	int level_map_width_;
	SDL_Texture*  level_map_;
};

inline int Scene::get_level_map_width() const
{
	return level_map_width_;
}

inline int Scene::get_level_map_height() const
{
	return level_map_height_;
}
