#pragma once

#include "glm/glm.hpp"

class settings
{
public:
	static settings& instance();

	//����� ����
	glm::ivec2 window_size{ 1280, 720 };
	//������������� �����
	bool fullscreen{ false };

	//����� ����
	glm::ivec2 world_size{ 0, 0 };
	//����� �����
	glm::ivec2 block_size{ 64, 64 };
	//��������� ����� ����
	glm::ivec2 pixel_world_size{ 0, 0 };


	//�������� ������
	float player_speed{ 1000 };
	//�����
	bool fog{ false };
	//������� �����
	int r_visble_area{ 5 };
	int r_visble_area_1{ 5 };
	int r_visble_area_2{ 25 };

	//������� �������
	unsigned int n_ammo{ 3 };
	//�������� �������
	unsigned int bullet_speed{ 100 };
	//��������� ��� �� ���������
	unsigned int time_between_shots{ 500 };
private:
	settings() = default;
};

