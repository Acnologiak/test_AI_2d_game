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
	glm::ivec2 world_size{ 32, 32 };
	//����� �����
	glm::ivec2 block_size{ 64, 64 };
	//��������� ����� ����
	glm::ivec2 pixel_world_size{ 2048, 2048 };

	float player_speed{ 1000 };
private:
	settings() = default;
};

