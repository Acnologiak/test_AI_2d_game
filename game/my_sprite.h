#pragma once

#include <string>

#include "glm/glm.hpp"
#include "Framework.h"


class my_sprite
{
	bool status{ false };
public:
	Sprite* texture;
	glm::ivec2 size;
	glm::ivec2 center;
	glm::ivec2 box_template[4];

	void load_sprite(std::string);
	bool get_status() { return status; };
};

