#include "stdafx.h"
#include "scene.h"

const std::string Scene::kCommonLevelMapPath = "Levels/level_map_";

Scene::Scene(void): level_map_width_(0),level_map_height_(0),level_map_(NULL)
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