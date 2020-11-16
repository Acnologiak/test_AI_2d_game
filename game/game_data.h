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
	int id;
	my_sprite spr;
	glm::ivec2 position;
	glm::ivec2 last_position;

	//�����?
	bool alive = true;
	//��� ��������� �������
	int last_time_shot{ 0 };

	std::vector<std::pair<glm::vec2, glm::vec2>> bullets;
private:

};

class game_data
{
public:
	static game_data& instance();

	//������� ����
	char** world_matrix;
	char** info_matrix;

	//������� ������ 
	glm::ivec2 camera_position{ 1000, 0 };

	//����� ����
	std::map<char, my_sprite> blocks;
	//����
	std::vector<creature> bots;
	//����
	my_sprite bullet;

private:
	game_data() = default;
};

