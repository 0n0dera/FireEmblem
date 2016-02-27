#pragma once
class Game
{
public:
	// public member variables

	// public methods
	Game();
	~Game();
	void init();
	void main_loop();
	void clean();

private:
	// private member variables
	bool m_is_running;
	bool m_is_fullscreen;
	SDL_Surface* m_screen;
	SDL_Window*  m_window;

	// private methods
	void handle_events();
	void update();
	void draw();
	void quit();
	void toggle_fullscreen();
};

