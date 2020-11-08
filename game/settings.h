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
	glm::ivec2 world_size;
	//розм≥р блоку
	glm::ivec2 block_size{ 64, 64 };
	//п≥ксельний розм≥р св≥ту
	glm::ivec2 pixel_world_size{ 0, 0 };

	//швидк≥сть гравц€
	float player_speed{ 1000 };
	//в≥льна камера
	bool free_cam{ true };
private:
	settings() = default;
};

