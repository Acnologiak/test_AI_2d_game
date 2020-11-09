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
		if (p == 16)
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
	for (auto& i : g_data.bots)
	{
		glm::vec2 p1, p2;
		p2.x = inp.cursor_pos.x - i.position.x - g_data.camera_position.x;
		p2.y = inp.cursor_pos.y - i.position.y - g_data.camera_position.y;
		n_normalize(p2);

		i.position += alpha * p2 * set.player_speed;
		
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
						//std::cout << "!";
						glm::ivec2 p{ c_n.x * set.block_size.x, c_n.y * set.block_size.y };
						int r = check_crossing(g_data.blocks['0'], p, b.spr, b.position);
						/*if (r == 0)
						{
							b.position.y = (c.y + 1) * set.block_size.y;
						}*/
						/*else if (r == 1)
						{
							b.position.x = (c.x + 1) * set.block_size.x;
						}
						else if (r == 2)
						{
							b.position.y = (c.y + 1) * set.block_size.y;
						}
						else if (r == 3)
						{
							b.position.x = c.x * set.block_size.x;
						}*/

					}
				}
			}
		}
	}
	
}
