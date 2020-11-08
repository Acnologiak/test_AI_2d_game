#pragma once

#include <vector>
#include <map>
#include <string>
#include <utility>
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
	my_sprite spr;
private:

};

class game_data
{
public:
	//������� ����
	char** world_matrix;
	char** info_matrix;

	//������� ������ 
	glm::ivec2 camera_position{ 0, 0 };

	//����� ����
	std::map<char, my_sprite> blocks;
	//����
	std::vector<creature> bots;

	static game_data& instance();
private:
	game_data() = default;
};

