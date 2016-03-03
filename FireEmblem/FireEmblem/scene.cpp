#include "stdafx.h"
#include "scene.h"

const std::string Scene::kCommonLevelMapPath = "Levels/level_map_";

Scene::Scene(void): level_map_width_(0),level_map_height_(0),level_map_(nullptr),movement_grid_ready_(false),attack_tiles_(std::vector<std::pair<int,int>>()),move_tiles_(std::vector<std::pair<int,int>>())
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
}

void Scene::draw_movement_grid(const Character* const player, const Camera& camera, SDL_Renderer* renderer)
{
	if (!movement_grid_ready_)
	{
		int p_x = player->get_x() / globals.TILE_SIZE;
		int p_y = player->get_y() / globals.TILE_SIZE;
		int steps = player->get_num_steps();
		int atk = player->get_attack_range();
		int left_x = std::max(p_x/globals.TILE_SIZE-steps-atk, 0);
		int right_x = std::min(p_x/globals.TILE_SIZE+steps+atk, level_map_width_/globals.TILE_SIZE - 1);
		int top_y = std::max(p_y/globals.TILE_SIZE-steps-atk,0);
		int bot_y = std::min(p_y/globals.TILE_SIZE+steps+atk,level_map_height_/globals.TILE_SIZE - 1);
		int grid_size = 2 * (steps + atk) + 1;
		bool** visited = new bool*[grid_size];
		for (int i = 0; i < grid_size; i++)
		{
			visited[i] = new bool[grid_size];
			for (int j = 0; j < grid_size; j++)
			{
				visited[i][j] = false;
			}
		}
		recur_move_grid(p_x, p_y, steps, p_x, p_y, player->get_num_steps,player->get_attack_range, visited);
		/*for (int i=left_x;i<=right_x;i++)
		{
			for (int j=top_y;j<=bot_y;j++)
			{
				int dist = std::abs(i-p_x/globals.TILE_SIZE)+std::abs(j-p_y/globals.TILE_SIZE);
				if (dist == steps + atk)
				{
					attack_tiles_.push_back(std::pair<int,int>(i*globals.TILE_SIZE,j*globals.TILE_SIZE));
				}
				else if (dist <= steps)
				{
					move_tiles_.push_back(std::pair<int,int>(i*globals.TILE_SIZE,j*globals.TILE_SIZE));
				}
			}
		}*/
		for (int i = 0; i < grid_size; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;

		movement_grid_ready_ = true;
	}
	render_grid(camera, renderer);
	
}

void Scene::recur_move_grid(int x, int y, int steps_left, const int p_x, const int p_y, const int steps, const int atk, bool**& visited)
{
	int arr_x = x - p_x + steps + atk;
	int arr_y = y - p_y + steps + atk;
	visited[arr_x][arr_y] = true;

	if (steps_left == 0)
	{
		if (!visited[arr_x][arr_y - 1] && )
		{

		}
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