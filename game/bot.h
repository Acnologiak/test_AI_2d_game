#pragma once

#include "glm/glm.hpp"

#include <list>
#include <vector>

struct bullet
{
	glm::ivec2 start_position;
	glm::ivec2 end_position;
	glm::vec2 direction_movement;
	glm::vec2 current_position;
};

class bot
{
public:
	~bot();

	int team{ 0 };
	bool alive{ true };

	glm::vec2 bot_position;
	glm::ivec2 chunk;

	bool ch_cros[4];

	std::list<glm::ivec2> way_movement;
	glm::vec2 direction_movement;
	glm::vec2 direction_viewing{ -1, 0 };

	std::vector<std::vector<bool>> visible_area;
	int size_visible_area{ 0 };

	int last_time_shot{ 0 };
	std::vector<bullet> bullets;
	std::vector<int> k_bots;

	int focusing_bot{ -1 };
	
	int status{ 0 };
private:
};

