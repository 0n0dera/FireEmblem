#pragma once

#include "scene.h"
#include "camera.h"
#include "current_tile.h"
#include "player_menu.h"

class Game
{
public:
	Game();
	~Game();
	bool init();
	void main_loop();
	void clean();

private:
	enum GameState{ 
		none,			// default
		player_select,	// player selected a unit
		player_move,	// unit is moving
		player_menu,	// unit has attacked, only menu
		player_attack,	// unit has stopped moving and can attack
		fight,			// fight scene
		player_done,
		enemy_move		// enemy is moving
	};

	// core methods
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
	void change_level();

	// movement related methods
	void inc_cur_tile_x(int amount);
	void inc_cur_tile_y(int amount);
	void move_player();
	void after_player_move();
	void reset_camera();

	// button press handlers
	void handle_z_press();
	void handle_x_press();
	void handle_down_press();
	void handle_up_press();
	void handle_right_press();
	void handle_left_press();

	// menu/attack related methods

	// updating position/end of turn methods
	void update_enemy_positions();
	void update_player_positions();
	void player_unit_is_done();

	// helper methods
	int get_unit_array_pos(const int x, const int y);

	int level_;
	GameState game_state_;
	bool is_running_;
	bool is_fullscreen_;
	SDL_Window* window_;
	SDL_Surface*  screen_;
	SDL_Renderer* renderer_;
	Scene scene_;
	Camera camera_;
	CurrentTile current_tile_;
	std::vector<Character*> player_vector_;
	std::vector<Character*> enemy_vector_;
	std::vector<Character*> character_map_;
	Character* current_player_;
	int saved_player_x_;
	int saved_player_y_;
	int saved_camera_x_;
	int saved_camera_y_;
	PlayerMenu player_menu_;
};
