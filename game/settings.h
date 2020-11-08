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
	glm::ivec2 world_size;
	//����� �����
	glm::ivec2 block_size{ 64, 64 };
	//��������� ����� ����
	glm::ivec2 pixel_world_size{ 0, 0 };
private:
	settings() = default;
};

