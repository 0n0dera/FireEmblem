#pragma once
class Game
{
public:
	// public member variables

	// public methods
	Game();
	~Game();
	bool init();
	void main_loop();
	void clean();

private:
	// private member variables
	const static std::string COMMON_LEVEL_MAP_PATH;
	int m_level;
	bool m_is_running;
	bool m_is_fullscreen;
	SDL_Surface*  m_screen;
	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture*  m_level_map;
	SpriteSheet m_sprite_sheet;

	// private methods
	void change_level();
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
};

