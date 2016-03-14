#pragma once
#include "camera.h"
#include "character.h"
#include <map>

class Scene
{
public:
	enum TileType{
		none,
		move,
		attack
	};

	static int get_level_map_height();
	static int get_level_map_width();
	static int get_level_map_height_tiles();
	static int get_level_map_width_tiles();

	Scene(SDL_Renderer* renderer);
	~Scene(void);
	void draw_level_map(const Camera& camera, SDL_Renderer* renderer) const;
	void change_level_map(int level, SDL_Renderer* renderer);
	void draw_movement_grid(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer);
	void draw_selected_tile(const int x, const int y, const int size, bool attack, SDL_Renderer* renderer);
	void movement_grid_not_ready();
	void draw_attack_range(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer);
	TileType get_grid_tile_from_real_coords(int x, int y) const;
	const std::vector<std::pair<int,int>>& get_attack_tiles() const;
	const std::vector<std::pair<int,int>>& get_move_tiles() const;
	const std::vector<std::pair<int,int>>& get_attack_range() const;
	const std::vector<bool>& get_impassable_terrain() const;
	void set_impassable_terrain(int index, bool val);

private:
	static const std::string kCommonLevelMapPath;

	void render_grid(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer);
	void recur_move_grid(int tile_x, int tile_y, int steps_left, const int grid_size, const int offset_x, const int offset_y, const int min_atk, const int max_atk);	
	bool is_tile_blocked(const int tile_x, const int tile_y);

	static int level_map_height_;
	static int level_map_width_;
	static int level_map_height_tiles_;
	static int level_map_width_tiles_;

	bool movement_grid_ready_;
	SDL_Texture* level_map_;
	SDL_Texture* blue_tile_;
	SDL_Texture* red_tile_;
	SDL_Texture* select_tile_;
	
	std::vector<TileType> grid_tiles_;
	std::vector<std::pair<int,int>> attack_tiles_;
	std::vector<std::pair<int,int>> move_tiles_;
	std::vector<std::pair<int,int>> attack_range_;
	std::vector<bool> impassable_terrain_;
};

inline int Scene::get_level_map_width()
{
	return level_map_width_;
}

inline int Scene::get_level_map_height()
{
	return level_map_height_;
}
inline int Scene::get_level_map_width_tiles()
{
	return level_map_width_tiles_;
}

inline int Scene::get_level_map_height_tiles()
{
	return level_map_height_tiles_;
}
inline const std::vector<std::pair<int,int>>& Scene::get_attack_range() const
{
	return attack_range_;
}
inline const std::vector<std::pair<int,int>>& Scene::get_move_tiles() const
{
	return move_tiles_;
}
inline const std::vector<std::pair<int,int>>& Scene::get_attack_tiles() const
{
	return attack_tiles_;
}
inline const std::vector<bool>& Scene::get_impassable_terrain() const
{
	return impassable_terrain_;
}