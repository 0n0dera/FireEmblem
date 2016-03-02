#pragma once
#include "camera.h"
#include "Characters\character.h"
#include <map>

class Scene
{
public:
	Scene(void);
	~Scene(void);
	void draw_level_map(const Camera& camera, SDL_Renderer* renderer) const;
	void change_level_map(int level, SDL_Renderer* renderer);
	int get_level_map_height() const;
	int get_level_map_width() const;
	void draw_movement_grid(const Character* const player, SDL_Renderer* renderer);
	void movement_grid_not_ready();
	std::vector<std::pair<int,int>> attack_tiles_;
	std::vector<std::pair<int,int>> move_tiles_;

private:
	static const std::string kCommonLevelMapPath;
	void render_grid(SDL_Renderer* renderer);
	
	bool movement_grid_ready_;
	int level_map_height_;
	int level_map_width_;
	SDL_Texture*  level_map_;
	bool** terrain_map_;
	
};

inline int Scene::get_level_map_width() const
{
	return level_map_width_;
}

inline int Scene::get_level_map_height() const
{
	return level_map_height_;
}