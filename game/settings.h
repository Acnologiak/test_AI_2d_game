#pragma once

#include "glm/glm.hpp"


class settings
{
public:
	static settings& instance();

	//����� �������
	bool spectator_mode{ true };
	// ������� �����
	bool thermal_map{ false };
	//����� ���� ��� ������ ���
	int bot_number_for_game{ 0 };
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
	int error_destination{ 16 };
	//����� ������ ���������� �����
	int find_way_r{ 10 };
	//���������� ��������� ��� ������ �����
	int find_way_e_increase{ 1 };
	//���������� ��� ��������� ������ �����
	float find_way_z{ 100 };

	//���������� �����������
	int e_aggressive{ 100 };
	//����� �����������
	int r_aggressive{ 3 };
private:
	settings() = default;
};

