#pragma once
#include "scene.h"
#include "camera.h"
#include "current_tile.h"
#include "player.h"

class Game
{
public:
	Game();
	~Game();
	bool init();
	void main_loop();
	void clean();

private:
	enum GameState{ none, player_select, player_move, player_attack, player_done, fight, enemy_move };
	void change_level();
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
	void highlight_cur_tile();
	void inc_cur_tile_x(int amount);
	void inc_cur_tile_y(int amount);
	void handle_z_press();
	void move_player();
	void after_player_move();

	int level_;
	GameState game_state_;
	bool is_running_;
	bool is_fullscreen_;
	SDL_Surface*  screen_;
	SDL_Window*   window_;
	SDL_Renderer* renderer_;
	Scene scene_;
	Camera camera_;
	CurrentTile current_tile_;
	std::vector<Player> player_vector_;
	Player* current_player_p_;
};
