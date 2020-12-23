#pragma once

#include "game_data.h"
#include "input.h"
#include "operations_with_vectors.h"

#include <list>
#include <vector>
#include <set>
#include <math.h>


struct block_for_find_way
{
	glm::ivec2 last_block{ -1, -1 };
	int sum{ 0 };
	int n_steps{ 0 };
};

class bot_logic
{
public:
	static bot_logic& instance();

	void check_crossing_bots();
	std::list<glm::ivec2> find_way(glm::ivec2 p1, glm::ivec2 p2, int** thermal_matrix);
	void update_chunk(bot& bob);

	void bot_movement(bot& bob, float alpha);
	void move_player(bot& bob, float alpha);

	void update_visible_area(bot& bob);
	void update_direction_viewing(bot& bob);

	void shooting_player(bot& bob, float t);
	void shooting_bot(bot& bob, float t);
	void move_bullets(bot& bob, float alpha);
	//перевырки для снарядів
	void check_bullets(bot& bob);
private:
	game_data& g_data = game_data::instance();
	settings& set = settings::instance();
	input& inp = input::instance();

	//перевірка перетину бота з об'єктом
	void check_crossing_bot(bot& bob);
	//рух до точки маршруту
	void m_bot_movement(bot& bob, float alpha);
	//перевірка чи викоанв бот міні ціль
	void check_m_bot(bot& bob);

	


	bot_logic() = default;
};

