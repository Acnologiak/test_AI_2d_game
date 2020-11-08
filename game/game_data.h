#pragma once

#include <vector>
#include <string>
#include "Framework.h"
#include "glm/glm.hpp"


class my_sprite
{
	bool status = false;
public:
	Sprite* texture;
	glm::ivec2 size;
	glm::ivec2 center;
	glm::ivec2 box_template[4];

	void load_sprite(std::string);
	bool get_status();
};

class creature
{
public:

private:

};

class game_data
{
public:
	char** world_matrix;
	char** info_matrix;

	std::vector<my_sprite> blocks;
	std::vector<creature> bots;

	static game_data& instance();
private:
	game_data() = default;
};

