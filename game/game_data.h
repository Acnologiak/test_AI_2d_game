#pragma once

#include "world.h"
#include "my_sprite.h"
#include "settings.h"

#include "learning_functions.h"

class game_data
{
public:
	static game_data& instance();

	void update_thermal_matrix_1();
	void normalize_update_thermal_matrix_1();

	void update_thermal_matrix_2();
	void normalize_update_thermal_matrix_2();

	world my_world;
	
	glm::ivec2 camera_pos;

	my_sprite block_0;
	my_sprite block_1;
	my_sprite team_1;
	my_sprite bullet;
	my_sprite thermal_blocks[64];
private:
	game_data() = default;

	settings& set = settings::instance();
};

