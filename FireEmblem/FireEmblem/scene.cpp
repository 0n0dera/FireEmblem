#include "stdafx.h"
#include "scene.h"
#include <fstream>
#include <sstream>

const std::string Scene::kCommonLevelMapPath = "Levels/level_map_";

Scene::Scene(void): 
	attack_tiles_(std::vector<std::pair<int,int>>()),move_tiles_(std::vector<std::pair<int,int>>()),
	movement_grid_ready_(false),level_map_height_(0),level_map_width_(0),level_map_height_tiles_(0),level_map_width_tiles_(0),level_map_(nullptr),terrain_map_(std::vector<bool>())
{
}


Scene::~Scene(void)
{
	SDL_DestroyTexture(level_map_);
}

void Scene::draw_level_map(const Camera& camera, SDL_Renderer* renderer) const
{
	SDL_RenderClear(renderer);
	SDL_Rect camera_rect = {camera.get_camera_x(), camera.get_camera_y(), globals.SCREEN_WIDTH, globals.SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, level_map_, &camera_rect, NULL);
}

void Scene::change_level_map(int level, SDL_Renderer* renderer)
{
	texture::load_texture_from_file(kCommonLevelMapPath + std::to_string(level) + ".png", level_map_, renderer);
	SDL_QueryTexture(level_map_,NULL,NULL,&level_map_width_,&level_map_height_);
	level_map_height_tiles_ = level_map_height_ / globals.TILE_SIZE;
	level_map_width_tiles_  = level_map_width_ / globals.TILE_SIZE;

	if (terrain_map_.size() > 0)
	{
		terrain_map_.clear();
	}

	// read level terrain txt file
	std::ifstream infile(kCommonLevelMapPath + std::to_string(level) + "_terrain.txt");
	std::string line;

	for (int i=0;i<level_map_height_tiles_;i++)
	{
		std::getline(infile,line);

		for (int j=0;j<level_map_width_tiles_;j++)
		{
			terrain_map_.push_back((line.at(j) == '1' ? false : true));
			std::cout << terrain_map_.at(i*level_map_width_tiles_+j);
		}
		std::cout << std::endl;
	}

	infile.close();
}

void Scene::draw_movement_grid(const Character* const player, const Camera& camera, const std::vector<Character*>& enemies, SDL_Renderer* renderer)
{
	if (!movement_grid_ready_)
	{
		move_tiles_.clear();
		attack_tiles_.clear();

		int tile_x = player->get_x() / globals.TILE_SIZE;
		int tile_y = player->get_y() / globals.TILE_SIZE;

		int steps = player->get_num_steps();
		int max_atk = player->get_max_attack_range();
		int min_atk = player->get_min_attack_range();

		int grid_size = 2 * (steps + max_atk) + 1;
		int** visited = new int*[grid_size];
		for (int i = 0; i < grid_size; i++)
		{
			visited[i] = new int[grid_size];
			for (int j = 0; j < grid_size; j++)
			{
				visited[i][j] = 0;
			}
		}
		int offset_x = tile_x - steps - max_atk;
		int offset_y = tile_y - steps - max_atk;

		recur_move_grid(tile_x, tile_y, steps, offset_x, offset_y, min_atk, max_atk, enemies, visited);
		
		for (int i = 0; i < grid_size; i++)
		{
			for (int j=0;j < grid_size;j++)
			{
				if (visited[i][j] == 1)
				{
					move_tiles_.push_back(std::pair<int,int>((i+offset_x)*globals.TILE_SIZE,(j+offset_y)*globals.TILE_SIZE));
				}
				else if (visited[i][j] == 2)
				{
					attack_tiles_.push_back(std::pair<int,int>((i+offset_x)*globals.TILE_SIZE,(j+offset_y)*globals.TILE_SIZE));
				}
			}
			delete[] visited[i];
		}
		delete[] visited;

		movement_grid_ready_ = true;
	}
	render_grid(camera, renderer);
	
}

void Scene::recur_move_grid(int tile_x, int tile_y, int steps_left, const int offset_x, const int offset_y, const int min_atk, const int max_atk, const std::vector<Character*>& enemies, int**& visited)
{
	int arr_x = tile_x - offset_x;
	int arr_y = tile_y - offset_y;
	visited[arr_x][arr_y] = 1;
		
	int cur_x;
	int cur_y;

	for (int i= -max_atk; i<=max_atk;i++)
	{
		for (int j=std::abs(i) - max_atk; j<=max_atk - std::abs(i);j++)
		{
			cur_x = tile_x + i;
			cur_y = tile_y + j;
			if (cur_x >= 0 && cur_x < level_map_width_tiles_ && cur_y >=0 && cur_y < level_map_height_tiles_)
			{
				if ((std::abs(i) + std::abs(j)) >= min_atk && visited[arr_x+i][arr_y+j] != 1)
				{
					visited[arr_x + i][arr_y + j] = 2;
				}
			}
		}
	}

	if (steps_left == 0) return;

	if (tile_y - 1 >= 0  && visited[tile_x][tile_y-1] != 1)
	{
		recur_move_grid(tile_x, tile_y-1, steps_left-1, offset_x, offset_y, min_atk,max_atk, enemies, visited);
	}
	if (tile_x + 1 < level_map_width_tiles_  && visited[tile_x+1][tile_y] != 1)
	{
		recur_move_grid(tile_x+1, tile_y, steps_left-1, offset_x, offset_y, min_atk,max_atk,enemies, visited);
	}
	if (tile_y + 1 < level_map_height_tiles_  && visited[tile_x][tile_y+1] != 1)
	{
		recur_move_grid(tile_x, tile_y+1, steps_left-1, offset_x, offset_y, min_atk,max_atk,enemies, visited);
	}
	if (tile_x - 1 >= 0  && visited[tile_x-1][tile_y] != 1)
	{
		recur_move_grid(tile_x-1, tile_y, steps_left-1, offset_x, offset_y,min_atk,max_atk, enemies, visited);
	}
}

void Scene::render_grid(const Camera& camera, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_Rect r;
	r.w =  globals.TILE_SIZE;
	r.h =  globals.TILE_SIZE;
	for (auto it = attack_tiles_.begin(); it != attack_tiles_.end(); ++it)
	{
		r.x = (*it).first - camera.get_camera_x();
		r.y = (*it).second - camera.get_camera_y();
		SDL_RenderFillRect(renderer,&r);
	}
	SDL_SetRenderDrawColor(renderer,0,0,255,255);
	for (auto it = move_tiles_.begin(); it != move_tiles_.end(); ++it)
	{
		r.x = (*it).first - camera.get_camera_x();
		r.y = (*it).second - camera.get_camera_y();
		SDL_RenderFillRect(renderer,&r);
	}
}

void Scene::movement_grid_not_ready()
{
	movement_grid_ready_ = false;
	attack_tiles_.clear();
	move_tiles_.clear();
}

bool Scene::is_tile_blocked(const int tile_x, const int tile_y, const std::vector<Character*>& enemies) const
{
	if (!terrain_map_.at(tile_y*level_map_width_tiles_+tile_x))
		return true;
	return false;
}