#pragma once
#include "scene.h"
#include "camera.h"
#include "current_tile.h"

class Game
{
public:
	Game();
	~Game();
	bool init();
	void main_loop();
	void clean();

private:
	void change_level();
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
	void highlight_cur_tile();
	void inc_cur_tile_x(int amount);
	void inc_cur_tile_y(int amount);

	int level_;
	bool is_running_;
	bool is_fullscreen_;
	SDL_Surface*  screen_;
	SDL_Window*   window_;
	SDL_Renderer* renderer_;
	Scene scene_;
	Camera camera_;
	CurrentTile current_tile_;
};
