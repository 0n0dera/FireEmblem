#pragma once
#include "camera.h"
#include "Characters\character.h"
#include <map>

class Scene
{
public:
	Scene(SDL_Renderer* renderer);
	~Scene(void);
	void draw_level_map(const Camera& camera, SDL_Renderer* renderer) const;
	void change_level_map(int level, SDL_Renderer* renderer);
	int get_level_map_height() const;
	int get_level_map_width() const;
	int get_level_map_height_tiles() const;
	int get_level_map_width_tiles() const;
	void draw_movement_grid(const Character* const player, const Camera& camera, const std::vector<Character*>& enemies, SDL_Renderer* renderer);
	void movement_grid_not_ready();
	std::vector<std::pair<int,int>> attack_tiles_;
	std::vector<std::pair<int,int>> move_tiles_;
	std::vector<bool> impassable_terrain_;

private:
	static const std::string kCommonLevelMapPath;
	void render_grid(const Camera& camera, SDL_Renderer* renderer);
	void recur_move_grid(int tile_x, int tile_y, int steps_left,const int offset_x, const int offset_y, const int min_atk, const int max_atk, const std::vector<Character*>& enemies, int**& visited);	
	bool is_tile_blocked(const int tile_x, const int tile_y);

	bool movement_grid_ready_;
	int level_map_height_;
	int level_map_width_;
	int level_map_height_tiles_;
	int level_map_width_tiles_;
	SDL_Texture* level_map_;
	SDL_Texture* blue_tile_;
	SDL_Texture* red_tile_;
	
};

inline int Scene::get_level_map_width() const
{
	return level_map_width_;
}

inline int Scene::get_level_map_height() const
{
	return level_map_height_;
}
inline int Scene::get_level_map_width_tiles() const
{
	return level_map_width_tiles_;
}

inline int Scene::get_level_map_height_tiles() const
{
	return level_map_height_tiles_;
}