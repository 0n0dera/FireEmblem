#pragma once

namespace texture
{

inline bool load_texture_from_file(const std::string path, SDL_Texture*& texture, SDL_Renderer* renderer)
{
	bool success = true;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		std::cout << "Unable to load image: " << path << "." << std::endl;
		success = false;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		SDL_FreeSurface(loaded_surface);
	}
	return success;
}

}