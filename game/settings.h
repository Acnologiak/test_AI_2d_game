#pragma once

#include "glm/glm.hpp"

class settings
{
public:
	static settings& instance();

	//розмір вікна
	glm::ivec2 window_size{ 1280, 720 };
	//повноекранний режим
	bool fullscreen{ false };

	//розмір світу
	glm::ivec2 world_size{ 8, 8 };
	//розмір блоку
	glm::ivec2 block_size{ 64, 64 };

	float player_speed{ 1000 };
private:
	settings() = default;
};

