#include "world.h"

#include <iostream>

//функція нормалізування
void n_normalize(glm::vec2& p)
{
	float f = sqrt(p.x * p.x + p.y * p.y);
	if (f != 0)
	{
		p.x = p.x / f;
		p.y = p.y / f;
	}
}

void my_sprite::load_sprite(std::string s)
{
	texture = createSprite(s.c_str());
	getSpriteSize(texture, size.x, size.y);

	box_template[0] = { 0, 0 };
	box_template[1] = { size.x, 0 };
	box_template[2] = { size.x, size.y };
	box_template[3] = { 0, size.y };

	center = { size.x / 2, size.y / 2 };

	status = true;
}

bool my_sprite::get_status()
{
	return status;
}

void player::update_player_position(float alpha)
{
	glm::vec2 p{ 0, 0 };
	if (inp.keyboard_up == true)
	{
		p.y -= 1;
	}
	if (inp.keyboard_down == true)
	{
		p.y += 1;
	}
	if (inp.keyboard_left == true)
	{
		p.x -= 1;
	}
	if (inp.keyboard_right == true)
	{
		p.x += 1;
	}
	//не працювала
	glm::normalize(p);
	n_normalize(p);

	position.x += p.x * alpha * set.player_speed;
	position.y += p.y * alpha * set.player_speed;
}

world& world::instance()
{
	static world instance;
	return instance;
}

void world::update_camera_position()
{
	glm::ivec2 p_pos = glm::ivec2{ pl.position } + pl.spr.center - set.window_size / 2;
	
	if (p_pos.x < 0)
	{
		p_pos.x = 0;
		camera_position.x = 0;
	}
	else
	{
		if (p_pos.x > set.pixel_world_size.x - set.window_size.x)
		{
			camera_position.x = -set.pixel_world_size.x + set.window_size.x;
		}
		else
		{
			camera_position.x = -p_pos.x;
		}
	}
	if (p_pos.y < 0)
	{
		p_pos.y = 0;
		camera_position.y = 0;
	}
	else
	{
		if (p_pos.y > set.pixel_world_size.y - set.window_size.y)
		{
			camera_position.y = -set.pixel_world_size.y + set.window_size.y;
		}
		else
		{
			camera_position.y = -p_pos.y;
		}
	}
}

bool world::load_world(std::string name)
{
	std::string s;
	std::ifstream file(name);
	if (!file.is_open())
	{
		return false;
	}
	
	//зчитання розміру світу
	file >> s;
	set.world_size.x = atoi(s.c_str());
	set.pixel_world_size.x = set.world_size.x * set.block_size.x;
	file >> s;
	set.world_size.y = atoi(s.c_str());
	set.pixel_world_size.y = set.world_size.y * set.block_size.y;

	//створення матриць для заповнення світу
	passage_matrix = new char* [set.world_size.x];
	for (int i = 0; i < set.world_size.x; i++)
	{
		passage_matrix[i] = new char[set.world_size.y];
	}
	world_matrix = new char* [set.world_size.x];
	for (int i = 0; i < set.world_size.x; i++)
	{
		world_matrix[i] = new char[set.world_size.y];
	}
	
	//зчитання світу
	char ch[1];
	for (int i = 0; i < set.world_size.x; i++)
	{
		file >> s;
		for (int j = 0; j < set.world_size.y; j++)
		{
			ch[0] = (char)s[j];
			passage_matrix[j][i] = atoi(ch);
		}
	}
	for (int i = 0; i < set.world_size.x; i++)
	{
		file >> s;
		for (int j = 0; j < set.world_size.y; j++)
		{
			ch[0] = (char)s[j];
			world_matrix[j][i] = atoi(ch);
		}
	}

	file.close();
	return true;
}
