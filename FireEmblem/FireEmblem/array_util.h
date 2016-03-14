#pragma once
#include "globals.h"
#include "scene.h"

namespace array_util
{
	inline int get_vector_pos_real_coords(const int x, const int y)
	{
		return y/globals.TILE_SIZE*Scene::get_level_map_width_tiles()+x/globals.TILE_SIZE;
	}
	inline int get_vector_pos_tile_coords(const int x, const int y)
	{
		return y*Scene::get_level_map_width_tiles() + x;
	}
}