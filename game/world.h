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
	//�����?
	bool alive = true;
	//�������
	int team;
	//��� ��������� �������
	int last_time_shot{ 0 };

	//������� ������
	glm::vec2 position;
	//��������� ������� ������
	glm::vec2 last_position;
	//������ �������
	bool** visible_area;
	//���
	std::vector<std::pair<glm::vec2, glm::vec2>> bullets;

	//��������� ������ ������
	void update_visible_area();
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
	my_sprite bullet;

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
	//������ ������
	void shooting_player();

	//�������� ������� ������
	void update_camera_position();
	//�������� ����
	bool load_world(std::string);
	//�������� �������� ������
	void check_players_crossing(creature& pl);
	//��� ����
	void move_bullets(float alpha);

	void update_bot_position(float alpha);
	void shooting_bot();
private:
	world() = default;

	input& inp = input::instance();
	settings& set = settings::instance();
};

class geneticalgorithma {
private:
	
	int i_generation = 0;
	//std::map<const int, std::shared_ptr<Enemy>> v_generation;
	
	

	bool m = true;
	
	double d_score = 0;

public:
	geneticalgorithma(world& world, int number);


};