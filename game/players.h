#pragma once

#include "game_data.h"
#include "input.h"
#include "settings.h"


class players
{
public:
	static players& instance();

	void spawn_bots();
private:
	players() = default;
	game_data& g_data = game_data::instance();
	input& inp = input::instance();
	settings& set = settings::instance();
};

