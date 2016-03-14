#include "stdafx.h"
#include "sprite_sheet.h"
#include "texture_util.h"
#include "array_util.h"
#include "scene.h"
#include <fstream>
#include <sstream>

const std::string Scene::kCommonLevelMapPath = "Levels/level_map_";

int Scene::level_map_height_ = 0;
int Scene::level_map_width_ = 0;
int Scene::level_map_height_tiles_ = 0;
int Scene::level_map_width_tiles_ = 0;

Scene::Scene(SDL_Renderer* renderer): 
	movement_grid_ready_(false),
	level_map_(nullptr),
	grid_tiles_(std::vector<TileType>()),
	attack_tiles_(std::vector<std::pair<int,int>>()),
	move_tiles_(std::vector<std::pair<int,int>>()),
	impassable_terrain_(std::vector<bool>()),
	blue_tile_(nullptr),
	red_tile_(nullptr),
	select_tile_(nullptr),
	attack_range_(std::vector<std::pair<int,int>>())
{
	texture_util::load_texture_from_file("Textures/blue_tile.png", blue_tile_, renderer);
	texture_util::load_texture_from_file("Textures/red_tile.png", red_tile_, renderer);
	texture_util::load_texture_from_file("Textures/select_tile.png", select_tile_, renderer);
	SDL_SetTextureBlendMode(blue_tile_,SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(red_tile_,SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(blue_tile_,155);
	SDL_SetTextureAlphaMod(red_tile_,155);
	change_level_map(1, renderer);
}


Scene::~Scene(void)
{
	SDL_DestroyTexture(level_map_);
	SDL_DestroyTexture(blue_tile_);
	SDL_DestroyTexture(red_tile_);
	SDL_DestroyTexture(select_tile_);
}

void Scene::draw_level_map(const Camera& camera, SDL_Renderer* renderer) const
{
	SDL_RenderClear(renderer);
	SDL_Rect camera_rect = {camera.get_camera_x(), camera.get_camera_y(), globals.SCREEN_WIDTH, globals.SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, level_map_, &camera_rect, NULL);
}

void Scene::change_level_map(int level, SDL_Renderer* renderer)
{
	texture_util::load_texture_from_file(kCommonLevelMapPath + std::to_string(level) + ".png", level_map_, renderer);
	SDL_QueryTexture(level_map_,NULL,NULL,&level_map_width_,&level_map_height_);
	level_map_height_tiles_ = level_map_height_ / Globals::TILE_SIZE;
	level_map_width_tiles_  = level_map_width_ / Globals::TILE_SIZE;

	if (impassable_terrain_.size() > 0)
	{
		impassable_terrain_.clear();
	}

	// read level terrain txt file
	std::ifstream infile(kCommonLevelMapPath + std::to_string(level) + "_terrain.txt");
	std::string line;

	for (int i=0;i<level_map_height_tiles_;i++)
	{
		std::getline(infile,line);

		for (int j=0;j<level_map_width_tiles_;j++)
		{
			impassable_terrain_.push_back((line.at(j) == '1' ? true : false));
			std::cout << impassable_terrain_.at(i*level_map_width_tiles_+j);
		}
		std::cout << std::endl;
	}

	infile.close();
}

void Scene::draw_selected_tile(const int x, const int y, const int size,bool attack, SDL_Renderer* renderer)
{
	SDL_Rect cur_tile_rect = {x, y, globals.TILE_SIZE+size, globals.TILE_SIZE+size};
	SDL_RenderCopy(renderer, select_tile_,NULL,&cur_tile_rect);
}

void Scene::draw_movement_grid(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer)
{
	if (!movement_grid_ready_)
	{
		int tile_x = player->get_x() / Globals::TILE_SIZE;
		int tile_y = player->get_y() / Globals::TILE_SIZE;

		int steps = player->get_num_steps();
		int max_atk = player->get_max_attack_range();
		int min_atk = player->get_min_attack_range();

		int grid_size = 2 * (steps + max_atk) + 1;

		move_tiles_.clear();
		attack_tiles_.clear();
		grid_tiles_.clear();
		grid_tiles_.resize(grid_size*grid_size, TileType::none);

		int offset_x = tile_x - steps - max_atk;
		int offset_y = tile_y - steps - max_atk;

		recur_move_grid(tile_x, tile_y, steps, grid_size, offset_x, offset_y, min_atk, max_atk);
		for (int i=0;i<grid_size;i++)
		{
			for (int j=0;j<grid_size;j++)
			{
				std::cout << grid_tiles_[i*grid_size+j];
			}
			std::cout << std::endl;
		}
		/*for (int i = 0; i < grid_size; i++)
		{
			for (int j = 0; j < grid_size;j++)
			{
				if (grid_tiles_[array_util::get_vector_pos_real_coords(i,j)] == move)
				{
					move_tiles_.push_back(std::pair<int,int>((j+offset_x)*Globals::TILE_SIZE,(i+offset_y)*Globals::TILE_SIZE));
				}
				else if (grid_tiles_[array_util::get_vector_pos_real_coords(i,j)] == attack)
				{
					attack_tiles_.push_back(std::pair<int,int>((j+offset_x)*Globals::TILE_SIZE,(i+offset_y)*Globals::TILE_SIZE));
				}
			}
		}*/

		movement_grid_ready_ = true;
	}
	render_grid(player, camera, renderer);
	
}

void Scene::recur_move_grid(int tile_x, int tile_y, int steps_left, const int grid_size, const int offset_x, const int offset_y, const int min_atk, const int max_atk)
{
	int arr_x = tile_x - offset_x;
	int arr_y = tile_y - offset_y;
	grid_tiles_[arr_y*grid_size+arr_x] = TileType::move;
	
	for (int i= -max_atk; i<=max_atk;i++)
	{
		for (int j=std::abs(i) - max_atk; j<=max_atk - std::abs(i);j++)
		{
			int cur_x = tile_x + i;
			int cur_y = tile_y + j;
			if (cur_x >= 0 && cur_x < level_map_width_tiles_ && cur_y >=0 && cur_y < level_map_height_tiles_)
			{
				if ((std::abs(i) + std::abs(j)) >= min_atk && grid_tiles_[(arr_y+j)*grid_size+(arr_x+i)] != TileType::move)
				{
					grid_tiles_[(arr_y+j)*grid_size+(arr_x+i)] = TileType::attack;
				}
			}
		}
	}

	if (steps_left == 0) return;

	if (tile_y - 1 >= 0 && !is_tile_blocked(tile_x, tile_y-1))
	{
		recur_move_grid(tile_x, tile_y-1, steps_left-1, grid_size, offset_x, offset_y, min_atk,max_atk);
	}
	if (tile_x + 1 < level_map_width_tiles_ && !is_tile_blocked(tile_x + 1, tile_y))
	{
		recur_move_grid(tile_x+1, tile_y, steps_left-1, grid_size, offset_x, offset_y, min_atk,max_atk);
	}
	if (tile_y + 1 < level_map_height_tiles_ && !is_tile_blocked(tile_x, tile_y+1))
	{
		recur_move_grid(tile_x, tile_y+1, steps_left-1, grid_size, offset_x, offset_y, min_atk,max_atk);
	}
	if (tile_x - 1 >= 0 && !is_tile_blocked(tile_x - 1,tile_y))
	{
		recur_move_grid(tile_x-1, tile_y, steps_left-1, grid_size, offset_x, offset_y,min_atk,max_atk);
	}
}

void Scene::render_grid(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.w =  globals.COLOR_TILE_SIZE;
	r.h =  globals.COLOR_TILE_SIZE;

	int size = grid_tiles_.size();
	int row_size = std::sqrt(size);
	int offset = player->get_num_steps()*globals.TILE_SIZE + player->get_max_attack_range()*globals.TILE_SIZE;

	for (int i=0;i<size;i++)
	{
		if (grid_tiles_[i] != TileType::none)
		{
			r.y = i/row_size*globals.TILE_SIZE+player->get_y() - offset - camera.get_camera_y();
			r.x = i%row_size*globals.TILE_SIZE+player->get_x() - offset - camera.get_camera_x();
			if (grid_tiles_[i] == TileType::move)
			{
				SDL_RenderCopy(renderer,blue_tile_,NULL, &r);
			}
			else
			{
				SDL_RenderCopy(renderer,red_tile_,NULL, &r);
			}
		}
	}

	/*for (auto it = attack_tiles_.begin(); it != attack_tiles_.end(); ++it)
	{
		r.x = (*it).first - camera.get_camera_x() + 1;
		r.y = (*it).second - camera.get_camera_y() + 1;
		SDL_RenderCopy(renderer, red_tile_, NULL, &r);
	}
	for (auto it = move_tiles_.begin(); it != move_tiles_.end(); ++it)
	{
		r.x = (*it).first - camera.get_camera_x() + 1;
		r.y = (*it).second - camera.get_camera_y() + 1;
		SDL_RenderCopy(renderer, blue_tile_, NULL, &r);
	}*/
}

void Scene::movement_grid_not_ready()
{
	movement_grid_ready_ = false;
	attack_tiles_.clear();
	move_tiles_.clear();
}

bool Scene::is_tile_blocked(const int tile_x, const int tile_y)
{
	return impassable_terrain_[array_util::get_vector_pos_tile_coords(tile_x,tile_y)];
}

void Scene::draw_attack_range(const std::shared_ptr<const Character>& player, const Camera& camera, SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.w =  globals.COLOR_TILE_SIZE;
	r.h =  globals.COLOR_TILE_SIZE;

	int max_atk = player->get_max_attack_range();
	int min_atk = player->get_min_attack_range();

	for (int i= -max_atk; i<=max_atk;i++)
	{
		for (int j=std::abs(i) - max_atk; j<=max_atk - std::abs(i);j++)
		{
			if ((i != 0 || j != 0) && std::abs(i)+std::abs(j) >= min_atk)
			{
				r.x = player->get_x()-camera.get_camera_x()-i*globals.TILE_SIZE;
				r.y = player->get_y()-camera.get_camera_y()-j*globals.TILE_SIZE;
				SDL_RenderCopy(renderer,red_tile_,NULL,&r);
			}
		}
	}
}

void Scene::set_impassable_terrain(int index, bool value)
{
	impassable_terrain_.at(index) = value;
}

Scene::TileType Scene::get_grid_tile_from_real_coords(int x, int y) const
{
	return grid_tiles_[y/globals.TILE_SIZE*std::sqrt(grid_tiles_.size())+x/globals.TILE_SIZE];
}