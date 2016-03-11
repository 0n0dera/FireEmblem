#pragma once

class Scene;
class Character;

class PlayerMenu
{
public:
	enum MenuSelection{
		atk_or_heal = 0,
		item =   1,
		wait =   2
	};
	PlayerMenu(void);
	~PlayerMenu(void);
	void draw(bool left_side, const std::shared_ptr<Character>& player, const Scene& scene, SDL_Renderer* renderer);
	int get_selection() const;
	void inc_selection(int inc);
	void set_can_attack(bool val);
	 
private:
	void draw_menu(const int x, const std::shared_ptr<Character>& player, SDL_Renderer* renderer);

	const int left_side_;
	const int right_side_;
	const int menu_y_;
	const int menu_width_;
	const int item_height_;
	int selection_;
	bool can_attack_;
};

inline int PlayerMenu::get_selection() const
{
	return selection_;
}


inline void PlayerMenu::set_can_attack(bool val)
{
	can_attack_ = val;
}