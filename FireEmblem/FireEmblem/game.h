#pragma once
#include "scene.h"
#include "camera.h"
#include "current_tile.h"
#include "Characters/character.h"

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
		player_attack,	// unit has stopped moving and can attack
		player_done,	// unit can't do anything else
		fight,			// fight scene
		enemy_move		// enemy is moving
	};
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
	SDL_Window* window_;
	SDL_Surface*  screen_;
	SDL_Renderer* renderer_;
	Scene scene_;
	Camera camera_;
	CurrentTile current_tile_;
	std::vector<Character*> player_vector_;
	std::vector<Character*> enemy_vector_;
	Character* current_player_;
};
