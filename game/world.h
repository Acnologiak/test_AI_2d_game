#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Framework.h"
#include "glm/glm.hpp"
#include "settings.h"
#include "input.h"


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
	my_sprite spr;
	glm::vec2 position;
	bool** visible_area;

	void update_visible_area();
	void update_bot_position(float);
protected:
	input& inp = input::instance();
	settings& set = settings::instance();
};


class world
{
public:
	static world& instance();

	Sprite* x;
	Sprite* y;
	Sprite* black;

	std::vector<creature> team1;
	std::vector<creature> team2;

	char** world_matrix;
	char** passage_matrix;

	creature* pl;

	glm::ivec2 camera_position;

	//перем≥щенн€ гравц€
	void update_player_position(float);

	void update_camera_position();
	bool load_world(std::string);
private:
	world() = default;

	input& inp = input::instance();
	settings& set = settings::instance();
};

