#include "world.h"

#include <iostream>

void my_sprite::load_sprite(std::string s)
{
	texture = createSprite(s.c_str());
	getSpriteSize(texture, size.x, size.y);

	box_template[0] = glm::ivec2{ 0, 0 };
	box_template[1] = glm::ivec2{ size.x, 0 };
	box_template[2] = glm::ivec2{ size.x, size.y };
	box_template[3] = glm::ivec2{ 0, size.y };

	center = { size.x / 2, size.y / 2 };

	status = true;
}

bool my_sprite::get_status()
{
	return status;
}

world& world::instance()
{
	static world instance;
	return instance;
}

void world::update_player_position(float alpha)
{
	pl->last_position = pl->position;

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

	pl->position.x += p.x * alpha * set.player_speed;
	pl->position.y += p.y * alpha * set.player_speed;
}

void world::shooting_player()
{
	if (getTickCount() - pl->last_time_shot >= set.time_between_shots)
	{
		glm::vec2 p1, p2;
		p1 = pl->position + glm::vec2{ pl->spr.center } - glm::vec2{ bullet.center };
		p2.x = inp.cursor_pos.x - pl->position.x - camera_position.x;
		p2.y = inp.cursor_pos.y - pl->position.y - camera_position.y;
		n_normalize(p2);

		pl->bullets.push_back(std::make_pair(p1, p2));
		pl->last_time_shot = getTickCount();
	}

	if (pl->bullets.size() > set.n_ammo)
	{
		pl->bullets.pop_front();
	}
}

void world::update_camera_position()
{
	glm::ivec2 p_pos = glm::ivec2{ pl->position } + pl->spr.center - set.window_size / 2;
	
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

void creature::update_visible_area()
{
	if (visible_area == nullptr)
	{
		visible_area = new bool* [set.world_size.x];
		for (int i = 0; i < set.world_size.x; i++)
		{
			visible_area[i] = new bool[set.world_size.y];
		}
	}
	
	glm::vec2 c{ position.x / set.block_size.x, position.y / set.block_size.y};
	for (int i = 0; i < set.world_size.x; i++)
	{
		for (int j = 0; j < set.world_size.y; j++)
		{
			if (pow((float)i - c.x, 2) + pow((float)j - c.y, 2) < set.r_visble_area_2)
			{
				visible_area[i][j] = true;
			}
			else
			{
				visible_area[i][j] = false;
			}
		}
	}
}

void creature::update_bot_position(float alpha)
{
}

void world::check_players_crossing(creature& pl)
{
	glm::ivec2 pos{ pl.position };

	glm::ivec2 c{ pos.x / set.block_size.x, pos.y / set.block_size.y };

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			glm::ivec2 c_n{ c.x + i , c.y + j };
			if (-1 < c_n.x and c_n.x < set.world_size.x and -1 < c_n.y and c_n.y < set.world_size.y)
			{
				if (passage_matrix[c_n.x][c_n.y] == 0)
				{
					glm::ivec2 p{ c_n.x * set.block_size.x, c_n.y * set.block_size.y };
					if (check_crossing(x, p, pl.spr, pos) == true)
					{
						pl.position = pl.last_position;
					}
				}
			}
		}
	}

	/*for (int i = 0; i < set.world_size.x; i++)
	{
		for (int j = 0; j < set.world_size.x; j++)
		{
			if (passage_matrix[i][j] == 0)
			{
				glm::ivec2 p{ i * set.block_size.x, j * set.block_size.y };
				if (check_crossing(x, p, pl.spr, pos) == true)
				{
					pl.position = pl.last_position;
				}
			}
			
		}
	}*/
}

void world::move_bullets(float alpha)
{
	for (auto& q : players)
	{
		std::list<std::list<std::pair<glm::vec2, glm::vec2>>::iterator> l;
		for (auto i = q.bullets.begin(); i != q.bullets.end(); i++)
		{
			(*i).first += (*i).second * alpha * set.bullet_speed;

			
			glm::ivec2 c{ (*i).first.x / set.block_size.x, (*i).first.y / set.block_size.y };
			for (int n = -1; n < 2; n++)
			{
				for (int m = -1; m < 2; m++)
				{
					glm::ivec2 c_n{ c.x + n , c.y + m };
					if (-1 < c_n.x and c_n.x < set.world_size.x and -1 < c_n.y and c_n.y < set.world_size.y)
					{
						if (passage_matrix[c_n.x][c_n.y] == 0)
						{
							glm::ivec2 p{ c_n.x * set.block_size.x, c_n.y * set.block_size.y };
							if (check_crossing(x, p, bullet, (*i).first) == true)
							{
								l.push_back(i);
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < l.size(); i++)
		{
			q.bullets.erase(l.back());
			l.pop_back();
		}
	}
}
