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
		enemy_move,		// enemy is moving
		turn_menu		// player presses z on empty tile
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
	void after_move_player();
	void move_enemy();
	void after_move_enemy();
	void reset_camera(const std::shared_ptr<Character>& unit);
	void camera_set(const std::shared_ptr<const Character>& unit);
	
	// button press handlers
	void handle_z_press();
	void handle_x_press();
	void handle_down_press();
	void handle_up_press();
	void handle_right_press();
	void handle_left_press();

	// menu/attack related methods
	bool check_enemies_in_range();
	
	// updating position/end of turn methods
	void update_unit_position(const std::shared_ptr<Character>& unit);
	void set_enemy_positions();
	void set_player_positions();
	void unit_is_done(const std::shared_ptr<Character>& unit);
	void players_not_grey();
	void enemies_not_grey();

	// helper methods
	void draw_characters();
	void enemy_phase();
	void create_players();

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
	
	std::shared_ptr<Character> null_ptr;
	std::vector<std::shared_ptr<Character>> player_vector_;
	std::vector<std::shared_ptr<Character>> enemy_vector_;
	std::vector<std::shared_ptr<Character>> character_map_;
	std::shared_ptr<Character> current_player_;
	std::shared_ptr<Character> mc_;

	std::vector<std::pair<int,int>> move_path_;

	int saved_camera_x_;
	int saved_camera_y_;
	PlayerMenu player_menu_;
	int active_players_;
	int active_enemies_;
};
