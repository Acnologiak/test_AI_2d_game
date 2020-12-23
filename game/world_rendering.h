#pragma once

#include "game_data.h"
#include "settings.h"
#include "input.h"

#include "operations_with_vectors.h"



class world_rendering
{
public:
	static world_rendering& instance();

	void draw_blocks();
	void draw_thermal_blocks();
	void update_camera_pos_spectator(float);
	void update_camera_pos_pl();
	void draw_bots();
	void draw_bullets();
private:
	game_data& g_data = game_data::instance();
	settings& set = settings::instance();
	input& inp = input::instance();
};

