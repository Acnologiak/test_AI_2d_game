#pragma once

#include "game_data.h"
#include "input.h"
#include "settings.h"
#include "utilities.h"


class players
{
public:
	static players& instance();

	void spawn_bots();
	void move_bots(float);
	void move_bot(creature& b, glm::vec2 v, float alpha);
	void shooting_bots();
	void shooting_bot(creature& b, glm::vec2 v);

	void check_crossing_pl();
	void update_last_position();
	//рух пуль
	void move_bullets(float alpha);
private:
	players() = default;
	game_data& g_data = game_data::instance();
	input& inp = input::instance();
	settings& set = settings::instance();
};

