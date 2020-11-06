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
	//живий?
	bool alive = true;
	//команда
	int team;
	//час останього вистр≥лу
	int last_time_shot{ 0 };

	//позиц≥€ гравц€
	glm::vec2 position;
	//попередн€ позиц≥€ гравц€
	glm::vec2 last_position;
	//видима область
	bool** visible_area;
	//пул≥
	std::vector<std::pair<glm::vec2, glm::vec2>> bullets;

	//оновленн€ видимоњ област≥
	void update_visible_area();
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
	my_sprite bullet;

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
	//ст≥льба гравц€
	void shooting_player();

	//онвленн€ позиц≥њ камери
	void update_camera_position();
	//загрузка св≥ту
	bool load_world(std::string);
	//перев≥рка перетину гравц€
	void check_players_crossing(creature& pl);
	//рух пуль
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