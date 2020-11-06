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
	//зображенн€ гравц€
	my_sprite spr;
	//бот?
	bool bot = true;
	//команда
	int team;

	//позиц≥€ гравц€
	glm::vec2 position;
	//попередн€ позиц≥€ гравц€
	glm::vec2 last_position;
	//видима область
	bool** visible_area;

	//оновленн€ видимоњ област≥
	void update_visible_area();
	//оновленн€ позиц≥њ бота
	void update_bot_position(float);
protected:
	input& inp = input::instance();
	settings& set = settings::instance();
};


class world
{
public:
	static world& instance();

	//спрайти блок≥в св≥ту
	my_sprite x;
	my_sprite y;
	my_sprite black;

	//гравц≥
	std::vector<creature> players;

	//матриц≥ дл€ в≥дображенн€ ≥ лог≥ки св≥ту
	char** world_matrix;
	char** passage_matrix;

	//гравець
	creature* pl;

	//позиц≥€ камери
	glm::ivec2 camera_position;

	//перем≥щенн€ гравц€
	void update_player_position(float);

	//онвленн€ позиц≥њ камери
	void update_camera_position();
	//загрузка св≥ту
	bool load_world(std::string);
	//перев≥рка перетину гравц€
	void check_players_crossing(creature& pl);
private:
	world() = default;

	input& inp = input::instance();
	settings& set = settings::instance();
};

