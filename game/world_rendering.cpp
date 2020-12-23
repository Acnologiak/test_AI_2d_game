#include "world_rendering.h"

world_rendering& world_rendering::instance()
{
	static world_rendering instance;
	return instance;
}

void world_rendering::draw_blocks()
{
	for (int i = 0; i < g_data.my_world.get_size_world().x; i++)
	{
		for (int j = 0; j < g_data.my_world.get_size_world().y; j++)
		{
			glm::ivec2 pos;
			pos.x = i * set.block_size.x - g_data.camera_pos.x;
			pos.y = j * set.block_size.y - g_data.camera_pos.y;
			
			if (g_data.my_world.world_matrix[i][j] == '0')
			{
				drawSprite(g_data.block_0.texture, pos.x, pos.y);
			}
			else if (g_data.my_world.world_matrix[i][j] == '1')
			{
				drawSprite(g_data.block_1.texture, pos.x, pos.y);
			}
		}
	}


	/*glm::ivec2 size_world = g_data.my_world.get_size_world();
	for (int i = -set.r_visible_area; i <= set.r_visible_area; i++)
	{
		for (int j = -set.r_visible_area; j <= set.r_visible_area; j++)
		{
			glm::ivec2 p;
			p.x = i + g_data.my_world.bots[1].chunk.x;
			p.y = j + g_data.my_world.bots[1].chunk.y;

			if (-1 < p.x and p.x < size_world.x and -1 < p.y and p.y < size_world.y)
			{
				if (g_data.my_world.bots[1].visible_area[i + set.r_visible_area][j + set.r_visible_area] != true)
				{
					glm::ivec2 pos;
					pos.x = p.x * set.block_size.x - g_data.camera_pos.x;
					pos.y = p.y * set.block_size.y - g_data.camera_pos.y;

					if (g_data.my_world.world_matrix[p.x][p.y] == '0')
					{
						drawSprite(g_data.block_0.texture, pos.x, pos.y);
					}
					else if (g_data.my_world.world_matrix[p.x][p.y] == '1')
					{
						drawSprite(g_data.block_1.texture, pos.x, pos.y);
					}
				}
			}
		}
	}*/
}

void world_rendering::draw_thermal_blocks()
{
	for (int i = 0; i < g_data.my_world.get_size_thermal_matrix_1().x; i++)
	{
		for (int j = 0; j < g_data.my_world.get_size_thermal_matrix_1().y; j++)
		{
			glm::ivec2 pos;
			pos.x = i * set.thermal_block_size.x - g_data.camera_pos.x;
			pos.y = j * set.thermal_block_size.y - g_data.camera_pos.y;

			int v = (g_data.my_world.thermal_matrix_1[i][j] - set.thermal_map_min) / 4;			
			if (v > 63)
			{
				v = 63;
			}

			if (g_data.my_world.world_matrix[i / 4][j / 4] != '0')
			{
				drawSprite(g_data.thermal_blocks[v].texture, pos.x, pos.y);
			}
			else
			{
				drawSprite(g_data.thermal_blocks[0].texture, pos.x, pos.y);
			}
		}
	}
}

void world_rendering::update_camera_pos_spectator(float alpha)
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

	g_data.camera_pos.x += p.x * alpha * set.cam_speed;
	g_data.camera_pos.y += p.y * alpha * set.cam_speed;
}

void world_rendering::update_camera_pos_pl()
{
	g_data.camera_pos = glm::ivec2{ g_data.my_world.bots[set.bot_number_for_game].bot_position } - set.window_size / 2;
}

void world_rendering::draw_bots()
{
	for (const auto& i : g_data.my_world.bots)
	{
		if (i.alive == false)
		{
			continue;
		}

		glm::ivec2 pos;
		pos.x = i.bot_position.x - g_data.camera_pos.x;
		pos.y = i.bot_position.y - g_data.camera_pos.y;

		if (i.team != -1)
		{
			drawSprite(g_data.team_1.texture, pos.x, pos.y);
		}
	}
}

void world_rendering::draw_bullets()
{
	for (auto& i : g_data.my_world.bots)
	{
		for (auto& j : i.bullets)
		{
			glm::ivec2 pos;
			pos.x = j.current_position.x - g_data.camera_pos.x;
			pos.y = j.current_position.y - g_data.camera_pos.y;

			drawSprite(g_data.bullet.texture, pos.x, pos.y);
		}
	}
}
