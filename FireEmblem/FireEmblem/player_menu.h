#pragma once

class Scene;
class Character;

class PlayerMenu
{
public:
	enum MenuSelection{
		attack = 0,
		heal = 1,
		item =   2,
		wait =   3
	};
	PlayerMenu(void);
	~PlayerMenu(void);
	void draw(bool left_side, const Scene& scene, SDL_Renderer* renderer);
	int get_selection() const;
	void inc_selection(int inc);
	void set_options(const std::shared_ptr<const Character>& player);
	 
private:
	void draw_menu(const int x, SDL_Renderer* renderer);

	std::vector<MenuSelection> options_vector_;
	const int left_side_;
	const int right_side_;
	const int menu_y_;
	const int menu_width_;
	const int item_height_;
	const int const_num_options_;
	int selection_;
	int can_attack_;
	int can_act_;
};
