#include "world.h"

#include <fstream>
#include "utilities.h"


world& world::instance()
{
	static world instance;
	return instance;
}

bool world::load_world(std::string path)
{
	std::string s, ss;
	std::ifstream file(path);
	if (!file.is_open())
	{
		return false;
	}

	//зчитання розміру блоків
	file >> s;
	set.block_size.x = atoi(s.c_str());
	file >> s;
	set.block_size.y = atoi(s.c_str());

	//зчитання розміру світу
	file >> s;
	set.world_size.x = atoi(s.c_str());
	set.pixel_world_size.x = set.world_size.x * set.block_size.x;
	file >> s;
	set.world_size.y = atoi(s.c_str());
	set.pixel_world_size.y = set.world_size.y * set.block_size.y;

	//створення матриць для заповнення світу
	g_data.info_matrix = new char* [set.world_size.x];
	for (int i = 0; i < set.world_size.x; i++)
	{
		g_data.info_matrix[i] = new char[set.world_size.y];
	}
	g_data.world_matrix = new char* [set.world_size.x];
	for (int i = 0; i < set.world_size.x; i++)
	{
		g_data.world_matrix[i] = new char[set.world_size.y];
	}

	//загрузка світу світу
	for (int i = 0; i < set.world_size.x; i++)
	{
		file >> s;
		for (int j = 0; j < set.world_size.y; j++)
		{
			g_data.info_matrix[j][i] = s[j];
		}
	}
	for (int i = 0; i < set.world_size.x; i++)
	{
		file >> s;
		for (int j = 0; j < set.world_size.y; j++)
		{
			g_data.world_matrix[j][i] = s[j];
		}
	}

	while (!file.eof())
	{
		file >> s;
		file >> ss;
		my_sprite x;
		x.load_sprite(ss);
		g_data.blocks.emplace(std::make_pair(s[0], x));
	}

	file.close();
	return true;
}

void world::draw_blocks()
{
	for (int i = 0; i < set.world_size.x; i++)
	{
		for (int j = 0; j < set.world_size.y; j++)
		{
			drawSprite(g_data.blocks[g_data.world_matrix[i][j]].texture, i * set.block_size.x - g_data.camera_position.x, j * set.block_size.y - g_data.camera_position.y);
		}
	}
}

void world::update_free_cam(float alpha)
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

	n_normalize(p);

	g_data.camera_position.x += p.x * alpha * set.player_speed;
	g_data.camera_position.y += p.y * alpha * set.player_speed;

	if (g_data.camera_position.x < 0)
	{
		g_data.camera_position.x = 0;
	}
	else
	{
		if (g_data.camera_position.x > set.pixel_world_size.x - set.window_size.x)
		{
			g_data.camera_position.x = set.pixel_world_size.x - set.window_size.x;
		}
	}
	if (g_data.camera_position.y < 0)
	{
		g_data.camera_position.y = 0;
	}
	else
	{
		if (g_data.camera_position.y > set.pixel_world_size.y - set.window_size.y)
		{
			g_data.camera_position.y = set.pixel_world_size.y - set.window_size.y;
		}
	}
}
