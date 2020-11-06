#pragma once

#include "glm/glm.hpp"

class settings
{
public:
	static settings& instance();

	//розм≥р в≥кна
	glm::ivec2 window_size{ 1280, 720 };
	//повноекранний режим
	bool fullscreen{ false };

	//розм≥р св≥ту
	glm::ivec2 world_size{ 0, 0 };
	//розм≥р блоку
	glm::ivec2 block_size{ 64, 64 };
	//п≥ксельний розм≥р св≥ту
	glm::ivec2 pixel_world_size{ 0, 0 };


	//швидк≥сть гравц€
	float player_speed{ 1000 };
	//туман
	bool fog{ false };
	//видимий рад≥ус
	int r_visble_area{ 5 };
	int r_visble_area_1{ 5 };
	int r_visble_area_2{ 25 };

	//к≥льк≥сть снар€д≥в
	unsigned int n_ammo{ 3 };
	//швидк≥сть снар€да
	unsigned int bullet_speed{ 100 };
	//м≥н≥мальний час м≥ж вистр≥лами
	unsigned int time_between_shots{ 500 };
private:
	settings() = default;
};

