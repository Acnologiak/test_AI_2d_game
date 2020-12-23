#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "glm/glm.hpp"
#include "bot.h"
#include "settings.h"

class world
{
public:
	world();
	~world();

	bool load_world(std::string name_world);
	void spawn_bots();


	bool get_status() { return status; };
	glm::ivec2 get_size_world() { return size_world; };
	glm::ivec2 get_size_thermal_matrix_1() { return size_thermal_matrix_1; };
	std::string get_name_world() { return name_world; };

	//������� ��� ����������� � ����� ����
	unsigned char** world_matrix;
	unsigned char** passage_matrix;

	//������ �������
	int** thermal_matrix_1;
	int** thermal_matrix_1_lite;
	int** thermal_matrix_2;
	
	int** thermal_matrix_1_for_bots;

	//����
	std::vector<bot> bots;

	//������� �� ������ � ����
	std::vector<bullet> u_bullets;
	//������� ���� ���� � ��������
	std::vector<glm::ivec2> u_bots;
private:
	settings& set = settings::instance();

	bool status{ false };
	glm::ivec2 size_world;
	glm::ivec2 size_thermal_matrix_1;
	std::string name_world;

	void save_thermal_matrix_1();
	void save_thermal_matrix_2();
};

