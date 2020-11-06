#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Framework.h"
#include "glm/glm.hpp"
#include "settings.h"
#include "input.h"
#include "utilities.h"


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
	//���������� ������
	my_sprite spr;
	//���?
	bool bot = true;
	//�������
	int team;

	//������� ������
	glm::vec2 position;
	//��������� ������� ������
	glm::vec2 last_position;
	//������ �������
	bool** visible_area;

	//��������� ������ ������
	void update_visible_area();
	//��������� ������� ����
	void update_bot_position(float);
protected:
	input& inp = input::instance();
	settings& set = settings::instance();
};


class world
{
public:
	static world& instance();

	//������� ����� ����
	my_sprite x;
	my_sprite y;
	my_sprite black;

	//������
	std::vector<creature> players;

	//������� ��� ����������� � ����� ����
	char** world_matrix;
	char** passage_matrix;

	//�������
	creature* pl;

	//������� ������
	glm::ivec2 camera_position;

	//���������� ������
	void update_player_position(float);

	//�������� ������� ������
	void update_camera_position();
	//�������� ����
	bool load_world(std::string);
	//�������� �������� ������
	void check_player_crossing(creature& pl);
private:
	world() = default;

	input& inp = input::instance();
	settings& set = settings::instance();
};

