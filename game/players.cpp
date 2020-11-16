#include "players.h"

#include <iostream>
players& players::instance()
{
	static players instance;
	return instance;
}

void players::spawn_bots()
{
	g_data.bots.clear();
	int p = 0;
	while (true)
	{
		if (p == 1)
		{
			break;
		}
		int x = rand() % set.world_size.x;
		int y = rand() % set.world_size.y;


		if (g_data.info_matrix[x][y] == '1')
		{
			creature c;
			c.spr.load_sprite("sprites/team1.png");
			c.position.x = (float)x * set.block_size.x + set.block_size.x / 2 - c.spr.center.x;
			c.position.y = (float)y * set.block_size.y + set.block_size.y / 2 - c.spr.center.y;
			c.id = p;
			p++;
			g_data.bots.emplace_back(c);
		}
	}
}

void players::move_bots(float alpha)
{
	/*for (auto& i : g_data.bots)
	{
				
	}*/
	if (g_data.bots[0].alive == true)
	{
		glm::vec2 p1, p2;
		p2.x = inp.cursor_pos.x - g_data.bots[0].position.x + g_data.camera_position.x;
		p2.y = inp.cursor_pos.y - g_data.bots[0].position.y + g_data.camera_position.y;

		n_normalize(p2);

		move_bot(g_data.bots[0], p2, alpha);
	}
}

void players::move_bot(creature& b, glm::vec2 v, float alpha)
{
	if (g_data.bots[0].alive == true)
	{
		b.position += alpha * v * set.player_speed;

		system("cls");

		std::cout << b.position.x << " " << b.position.y << std::endl;

		glm::vec2 current_possition = b.position + b.spr.center;

		std::vector<std::pair<std::string, glm::vec2>> inp_data;
		inp_data.emplace_back(std::make_pair<std::string, glm::vec2>("up -> ", glm::vec2 { 0, -1 }));
		inp_data.emplace_back(std::make_pair<std::string, glm::vec2>("down -> ", glm::vec2 { 0, 1 }));
		inp_data.emplace_back(std::make_pair<std::string, glm::vec2>("left -> ", glm::vec2 { -1, 0 }));
		inp_data.emplace_back(std::make_pair<std::string, glm::vec2>("right -> ", glm::vec2{ 1, 0 }));

		for (const auto& i : inp_data)
		{
			glm::vec2 v = i.second;

			v *= 4;
			glm::vec2 xx = current_possition;
			glm::ivec2 p{ xx.x / set.block_size.x,  xx.y / set.block_size.y };
			while (g_data.info_matrix[p.x][p.y] != '0')
			{
				xx += v;
				p = glm::ivec2{ xx.x / set.block_size.x, xx.y / set.block_size.y };
			}
			std::cout << i.first << abs(xx.x - current_possition.x) << " " << abs(xx.y - current_possition.y) << std::endl;
		}

		
	}
	
}

void players::shooting_bots()
{
	for (int i=0; i<0; i++)
	{
		for (int j = 0; j < g_data.bots.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				glm::vec2 v = g_data.bots[j].position - g_data.bots[i].position;
				
				if (glm::length(v) < 600)
				{
					n_normalize(v);
					shooting_bot(g_data.bots[j], -v);
				}
			}
		}
	}
}

void players::shooting_bot(creature& b, glm::vec2 v)
{
	if (b.alive == true)
	{
		if (getTickCount() - b.last_time_shot >= set.time_between_shots)
		{
			b.bullets.push_back(std::make_pair(b.position, v));
			b.last_time_shot = getTickCount();
		}
		if (b.bullets.size() > set.n_ammo)
		{
			b.bullets.erase(b.bullets.begin());
		}
	}	
}

void players::check_crossing_pl()
{
	for (auto& b : g_data.bots)
	{
		glm::ivec2 c{ b.position.x / set.block_size.x, b.position.y / set.block_size.y };

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				glm::ivec2 c_n{ c.x + i , c.y + j };
				if (-1 < c_n.x and c_n.x < set.world_size.x and -1 < c_n.y and c_n.y < set.world_size.y)
				{
					if (g_data.info_matrix[c_n.x][c_n.y] == '0')
					{
						glm::ivec2 p{ c_n.x * set.block_size.x, c_n.y * set.block_size.y };
						if (check_crossing(g_data.blocks['0'], p, b.spr, b.position) == true)
						{
							b.position = b.last_position;
						}
					}
				}
			}
		}
	}
	
}

void players::update_last_position()
{
	for (auto& i : g_data.bots)
	{
		i.last_position = i.position;
	}
}

void players::move_bullets(float alpha)
{
	for (int l=0; l< g_data.bots.size(); l++)
	{
		std::vector<int> arr;
		for (int i = 0; i < g_data.bots[l].bullets.size(); i++)
		{
			//рух пуль
			g_data.bots[l].bullets[i].first += g_data.bots[l].bullets[i].second * alpha * set.bullet_speed;

			//пошук пуль в ст≥нах
			glm::ivec2 c{ g_data.bots[l].bullets[i].first.x / set.block_size.x, g_data.bots[l].bullets[i].first.y / set.block_size.y };
			for (int n = -1; n < 2; n++)
			{
				for (int m = -1; m < 2; m++)
				{
					glm::ivec2 c_n{ c.x + n , c.y + m };
					if (-1 < c_n.x and c_n.x < set.world_size.x and -1 < c_n.y and c_n.y < set.world_size.y)
					{
						if (g_data.info_matrix[c_n.x][c_n.y] == '0')
						{
							glm::ivec2 p{ c_n.x * set.block_size.x, c_n.y * set.block_size.y };
							if (check_crossing(g_data.bots[l].spr, p, g_data.bullet, g_data.bots[l].bullets[i].first) == true)
							{
								arr.push_back(i);
							}
						}
					}
				}
			}

			//попаданн€ в гравц€
			for (int z=0; z < g_data.bots.size(); z++)
			{
				if (z != l)
				{
					if (g_data.bots[z].alive == true)
					{
						if (check_crossing(g_data.bots[z].spr, g_data.bots[z].position, g_data.bullet, g_data.bots[l].bullets[i].first) == true)
						{
							g_data.bots[z].alive = false;
							arr.push_back(i);
						}
					}
				}
			}

		}

		std::vector<std::pair<glm::vec2, glm::vec2>> bullets;

		if (!arr.empty())
		{
			for (int i = 0; i < g_data.bots[l].bullets.size(); i++)
			{
				if (!arr.empty())
				{
					if (i != arr.front())
					{
						bullets.emplace_back(g_data.bots[l].bullets[i]);
					}
					else
					{
						arr.erase(arr.begin());
					}
				}
				else
				{
					bullets.emplace_back(g_data.bots[l].bullets[i]);
				}
			}
			std::swap(g_data.bots[l].bullets, bullets);
		}
	}
}


