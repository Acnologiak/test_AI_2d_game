#pragma once

#include "glm/glm.hpp"

#include <string>

class settings
{
public:
	static settings& instance();

	//����� ����
	std::string name_world{ "1" };

	//����� �������� �������� ������ �� �������
	bool learning_mode{ false };
	//������� ����
	int n_epoch{ 10 };


	//����� �������
	bool spectator_mode{ false };
	// ������� �����
	bool thermal_map{ false };
	//����� ���� ��� ������ ���
	int bot_number_for_game{ 1 };
	//�������� ������
	float cam_speed{ 1000 };

	//����� ����
	glm::ivec2 window_size{ 1280, 720 };
	//������������� �����
	bool fullscreen{ false };

	//����� �����
	glm::ivec2 block_size{ 64, 64 };
	//����� ����� ������� �����
	glm::ivec2 thermal_block_size{ 16, 16 };
	//����� ����
	glm::ivec2 bot_size{ 32, 32 };
	//�������� ����
	float bot_speed{150};


	//������� �������
	unsigned int n_ammo{ 5 };
	//�������� �������
	float bullet_speed{ 150 };
	//��������� ��� �� ���������
	unsigned int time_between_shots{ 500 };

	//����� ��������
	int r_visible_area{ 8 };
	//���������� ��������� ��� ������ �����
	int find_direction_viewing_e_increase{ 1 };
	//����� �������� ��� ����������
	int r_direction_viewing_learning{ 5 };
	//���������� �������� ��� ����������
	int e_direction_viewing_learning{ 20 };

	//����� �������� ��� ����������
	int r_learning{ 10 };
	//���������� �������� ��� ����������
	int e_learning{ 10 };
	//�������� ������� ����� 
	int thermal_map_max{ 128 };
	//����� ������� ����� 
	int thermal_map_min{ -128 };

	//������� ��� ������ ���������� ����� �����������
	int error_destination{ 1 };
	//����� ������ ���������� �����
	int find_way_r{ 5 };
	//���������� ��������� ��� ������ �����
	int find_way_e_increase{ 10 };
	//���������� ��� ��������� ������ �����
	float find_way_z{ 100 };

	//���������� �����������
	int e_aggressive{ 300 };
	//����� �����������
	int r_aggressive{ 10 };
private:
	settings() = default;
};

