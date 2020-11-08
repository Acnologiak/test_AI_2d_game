#pragma once

#include <string>

#include "game_data.h"
#include "input.h"
#include "settings.h"


class world
{
public:
	static world& instance();

	bool load_world(std::string path);

	//відображення світу
	void draw_blocks();

	//онвлення позиції камери
	void update_free_cam(float);
private:
	world() = default;
	game_data& g_data = game_data::instance();
	input& inp = input::instance();
	settings& set = settings::instance();
};

