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
	// private member 
	const std::string COMMON_LEVEL_MAP_PATH;
	int m_level = 1;
	bool m_is_running = false;
	bool m_is_fullscreen = false;
	SDL_Surface*  m_screen;
	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture*  m_level_map;

	// private methods
	void change_level();
	void draw_level_map();
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
};

extern const int TILE_SIZE;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;