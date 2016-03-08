#pragma once

class Scene;
class Character;

class PlayerMenu
{
public:
	enum MenuSelection{
		attack = 0,
		heal =   0,
		item =   1,
		wait =   2
	};
	PlayerMenu(void);
	~PlayerMenu(void);
	void draw(const Character* const player, const Scene& scene, SDL_Renderer* renderer);
	int get_selection() const;
	 
private:
	void draw_select(SDL_Renderer* renderer);

	int selection_;
};

inline int PlayerMenu::get_selection() const
{
	return selection_;
}