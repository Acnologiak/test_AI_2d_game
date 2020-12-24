#include "bot_logic.h"

#include "operations_with_points.h"
#include <iostream>

bot_logic& bot_logic::instance()
{
	static bot_logic instance;
	return instance;
}

void bot_logic::check_crossing_bots()
{
	for (auto &i : g_data.my_world.bots)
	{
		for (int j = 0; j < 4; j++)
		{
			i.ch_cros[j] = false;
		}

		i.chunk = i.bot_position + glm::vec2{ set.bot_size / 2 };
		i.chunk.x = i.chunk.x / set.block_size.x;
		i.chunk.y = i.chunk.y / set.block_size.y;

		check_crossing_bot(i);

	}
}

std::list<glm::ivec2> bot_logic::find_way(glm::ivec2 p1, glm::ivec2 p2, int** thermal_matrix)
{
	glm::ivec2 size_world = g_data.my_world.get_size_world();
	float z = set.find_way_z;

	block_for_find_way** matrix = new block_for_find_way *[size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		matrix[i] = new block_for_find_way[size_world.y];
	}
	
	
	//for (int j = 0; j < size_world.y; j++)
	//{
	//	for (int i = 0; i < size_world.x; i++)
	//	{
	//		std::cout << g_data.my_world.thermal_matrix_1_lite[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	std::list<glm::ivec2> v_1, v_2;
	v_1.push_back(p1);
	while (true)
	{
		
		for (const auto& i : v_1)
		{
			float k{ 0 };

			if (i.y + 1 < size_world.y)
			{
				glm::ivec2 n_p{ i.x, i.y + 1 };
				if (g_data.my_world.passage_matrix[n_p.x][n_p.y] != '0')
				{
					if (matrix[n_p.x][n_p.y].last_block == glm::ivec2{ -1, -1 })
					{
						matrix[n_p.x][n_p.y].last_block = i;
						matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
						matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

						v_2.push_back(n_p);
					}
					else
					{
						/*k = (float)(matrix[i.x][i.y].sum + thermal_matrix[n_p.x][n_p.y]) / (float)(z * (matrix[i.x][i.y].n_steps + 1));

						bool b = true;
						glm::ivec2 g_1{ i.x, i.y };
						while (true)
						{
							if (g_1.x == p1.x and g_1.y == p1.y)
							{
								b = false;
								break;
							}
							else
							{
								if (g_1.x == n_p.x and g_1.y == n_p.y)
								{
									b = false;
									break;
								}
								else
								{
									g_1 = matrix[g_1.x][g_1.y].last_block;
								}
							}
						}
						if (b == true)
						{
							if (k > (float)matrix[n_p.x][n_p.y].sum / (float)matrix[n_p.x][n_p.y].n_steps)
							{
								matrix[n_p.x][n_p.y].last_block = i;
								matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
								matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

								v_2.push_back(n_p);
							}
						}*/
					}
				}
			}
			if (i.x + 1 < size_world.x)
			{
				glm::ivec2 n_p{ i.x + 1, i.y };
				if (g_data.my_world.passage_matrix[n_p.x][n_p.y] != '0')
				{
					if (matrix[n_p.x][n_p.y].last_block == glm::ivec2{ -1, -1 })
					{
						matrix[n_p.x][n_p.y].last_block = i;
						matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
						matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

						v_2.push_back(n_p);
					}
					else
					{
						/*bool b = true;
						glm::ivec2 g_1{ i.x, i.y };
						while (true)
						{
							if (g_1.x == p1.x and g_1.y == p1.y)
							{
								b = false;
								break;
							}
							else
							{
								if (g_1.x == n_p.x and g_1.y == n_p.y)
								{
									b = false;
									break;
								}
								else
								{
									g_1 = matrix[g_1.x][g_1.y].last_block;
								}
							}
						}
						if (b == true)
						{
							if (k > (float)matrix[n_p.x][n_p.y].sum / (float)matrix[n_p.x][n_p.y].n_steps)
							{
								matrix[n_p.x][n_p.y].last_block = i;
								matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
								matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

								v_2.push_back(n_p);
							}
						}*/
					}
				}
			}
			if (i.y - 1 > -1)
			{
				glm::ivec2 n_p{ i.x, i.y - 1 };
				if (g_data.my_world.passage_matrix[n_p.x][n_p.y] != '0')
				{
					if (matrix[n_p.x][n_p.y].last_block == glm::ivec2{ -1, -1 })
					{
						matrix[n_p.x][n_p.y].last_block = i;
						matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
						matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

						v_2.push_back(n_p);
					}
					else
					{
						/*bool b = true;
						glm::ivec2 g_1{ i.x, i.y };
						while (true)
						{
							if (g_1.x == p1.x and g_1.y == p1.y)
							{
								b = false;
								break;
							}
							else
							{
								if (g_1.x == n_p.x and g_1.y == n_p.y)
								{
									b = false;
									break;
								}
								else
								{
									g_1 = matrix[g_1.x][g_1.y].last_block;
								}
							}
						}
						if (b == true)
						{
							if (k > (float)matrix[n_p.x][n_p.y].sum / (float)matrix[n_p.x][n_p.y].n_steps)
							{
								matrix[n_p.x][n_p.y].last_block = i;
								matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
								matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

								v_2.push_back(n_p);
							}
						}*/
					}
				}
			}
			if (i.x - 1 > -1)
			{
				glm::ivec2 n_p{ i.x - 1, i.y };
				if (g_data.my_world.passage_matrix[n_p.x][n_p.y] != '0')
				{
					if (matrix[n_p.x][n_p.y].last_block == glm::ivec2{ -1, -1 })
					{
						matrix[n_p.x][n_p.y].last_block = i;
						matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
						matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

						v_2.push_back(n_p);
					}
					else
					{
						/*bool b = true;
						glm::ivec2 g_1{ i.x, i.y };
						while (true)
						{
							if (g_1.x == p1.x and g_1.y == p1.y)
							{
								b = false;
								break;
							}
							else
							{
								if (g_1.x == n_p.x and g_1.y == n_p.y)
								{
									b = false;
									break;
								}
								else
								{
									g_1 = matrix[g_1.x][g_1.y].last_block;
								}
							}
						}
						if (b == true)
						{
							if (k > (float)matrix[n_p.x][n_p.y].sum / (float)matrix[n_p.x][n_p.y].n_steps)
							{
								matrix[n_p.x][n_p.y].last_block = i;
								matrix[n_p.x][n_p.y].sum = thermal_matrix[n_p.x][n_p.y] + matrix[i.x][i.y].sum;
								matrix[n_p.x][n_p.y].n_steps = 1 + matrix[i.x][i.y].n_steps;

								v_2.push_back(n_p);
							}
						}*/
					}
				}
			}
		}

		if (matrix[p2.x][p2.y].last_block != glm::ivec2{ -1, -1 })
		{
			break;
		}

		v_1.clear();
		std::swap(v_1, v_2);
	}

	std::list<glm::ivec2> way;
	way.push_front(p2);
	while (true)
	{
		if (matrix[way.front().x][way.front().y].last_block == p1)
		{
			break;
		}

		way.push_front(matrix[way.front().x][way.front().y].last_block);
	}

	for (int i = 0; i < size_world.x; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	return way;
}

void bot_logic::bot_movement(bot& bob, float alpha)
{
	//створенн€ маршруту
	if (bob.way_movement.size() == 0)
	{
		bob.status = 0;

		int h = set.thermal_map_min - 1;
		glm::ivec2 size_world = g_data.my_world.get_size_world();
		glm::ivec2 p{ 0, 0 };

		for (int i = -set.find_way_r; i <= set.find_way_r; i++)
		{
			for (int j = -set.find_way_r; j <= set.find_way_r; j++)
			{
				glm::ivec2 p_ch = bob.chunk + glm::ivec2{ i, j };
				if (p_ch.x > 0 and p_ch.x < size_world.x and
					p_ch.y > 0 and p_ch.y < size_world.y and g_data.my_world.passage_matrix[p_ch.x][p_ch.y]!='0')
				{
					int k = g_data.my_world.thermal_matrix_1_lite[p_ch.x][p_ch.y] + glm::length(glm::vec2{ i, j }) * set.find_way_e_increase + rand() % set.find_way_e_increase;
					if (k > h)
					{
						h = k;
						p = p_ch;
					}
				}
			}
		}
		
		//std::cout << g_data.my_world.thermal_matrix_1_lite[0][0] << std::endl;
		bob.way_movement = find_way(bob.chunk, p, g_data.my_world.thermal_matrix_1_lite);

	}


	//рух бота по задан≥й частин≥ маршруту
	m_bot_movement(bob, alpha);
	//перев≥рка чи бот пройшов задану частину маршруту
	check_m_bot(bob);
}

void bot_logic::update_chunk(bot& bob)
{
	bob.chunk.x = (bob.bot_position.x + set.bot_size.x / 2) / set.block_size.x;
	bob.chunk.y = (bob.bot_position.y + set.bot_size.y / 2) / set.block_size.y;
}

void bot_logic::move_player(bot& bob, float alpha)
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
	bob.direction_movement = p;

	bob.bot_position += p * alpha * set.bot_speed;
}

void bot_logic::update_visible_area(bot& bob)
{
	for (int i = 0; i < bob.size_visible_area; i++)
	{
		for (int j = 0; j < bob.size_visible_area; j++)
		{
			bob.visible_area[i][j] = false;
		}
	}
	
	float angle = asin(bob.direction_viewing.y);

	glm::ivec2 size_world = g_data.my_world.get_size_world();

	for (float i = -1; i <= 1; i += 1/(float)set.r_visible_area)
	{
		glm::vec2 direction;
		if (bob.direction_viewing.x > 0)
		{
			direction = glm::vec2{ cos(i + angle) / 3 * set.block_size.x, sin(i + angle) / 3 * set.block_size.x };
		}
		else
		{
			direction = glm::vec2{ -cos(i + angle) / 3 * set.block_size.x, sin(i + angle) / 3 * set.block_size.x };
		}

		glm::vec2 p_1 = bob.bot_position;
		while (true)
		{
			glm::ivec2 p_2 = glm::ivec2{ (p_1.x - bob.chunk.x) / set.block_size.x, (p_1.y - bob.chunk.y) / set.block_size.y };
			if (glm::length(glm::vec2{ p_2 - bob.chunk }) < set.r_visible_area)
			{
				if (-1 < p_2.x and p_2.x < size_world.x and -1 < p_2.y and p_2.y < size_world.y)
				{
					if (g_data.my_world.passage_matrix[p_2.x][p_2.y] != '0')
					{
						bob.visible_area[p_2.x - bob.chunk.x + set.r_visible_area][p_2.y - bob.chunk.y + set.r_visible_area] = true;
						p_1 += direction;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	
}

void bot_logic::update_direction_viewing(bot& bob)
{
	if (bob.focusing_bot != -1)
	{
		bob.direction_viewing = -glm::normalize(bob.bot_position - g_data.my_world.bots[bob.focusing_bot].bot_position);

		if (g_data.my_world.bots[bob.focusing_bot].alive == false)
		{
			bob.focusing_bot = -1;
		}
		else
		{
			glm::ivec2 bot_pos = glm::ivec2{ bob.chunk } - g_data.my_world.bots[bob.focusing_bot].chunk + glm::ivec2{ set.r_visible_area, set.r_visible_area };
			if (!(-1 < bot_pos.x and bot_pos.x < bob.size_visible_area and -1 < bot_pos.y and bot_pos.y < bob.size_visible_area))
			{
				bob.focusing_bot = -1;
			}
			else if (bob.visible_area[bob.size_visible_area - bot_pos.x - 1][bob.size_visible_area - bot_pos.y - 1] == false)
			{
				bob.focusing_bot = -1;
			}
			
		}
	}
	else
	{
		int** maxtrix = g_data.my_world.thermal_matrix_2;

		int h = set.thermal_map_min - 1;
		glm::ivec2 size_world = g_data.my_world.get_size_world();
		glm::ivec2 p;

		for (int i = -set.r_visible_area; i <= set.r_visible_area; i++)
		{
			for (int j = -set.r_visible_area; j <= set.r_visible_area; j++)
			{
				glm::ivec2 p_ch = bob.chunk + glm::ivec2{ i, j };
				if (p_ch.x > 0 and p_ch.x < size_world.x and
					p_ch.y > 0 and p_ch.y < size_world.y and g_data.my_world.passage_matrix[p_ch.x][p_ch.y] != '0')
				{
					int k = maxtrix[p_ch.x][p_ch.y] + glm::length(glm::vec2{ i, j }) * set.find_direction_viewing_e_increase;
					if (k > h)
					{
						h = k;
						p = p_ch;
					}
				}
			}
		}

		bob.direction_viewing = -glm::normalize(glm::vec2{ bob.chunk - p });
	}
}

void bot_logic::shooting_player(bot& bob, float t)
{
	bob.direction_viewing = -glm::normalize(bob.bot_position - glm::vec2{ g_data.camera_pos } - glm::vec2{ inp.cursor_pos });
	//std::cout << bob.direction_viewing.x << " " << bob.direction_viewing.y << std::endl;

	if (inp.mouse_left == true)
	{
		if (t - bob.last_time_shot < set.time_between_shots)
		{
			return;
		}
		else
		{
			bullet b;
			b.start_position = glm::ivec2{ bob.bot_position } + set.bot_size / 2 - g_data.bullet.center;
			b.current_position = glm::ivec2{ bob.bot_position } + set.bot_size / 2 - g_data.bullet.center;
			b.direction_movement = -glm::normalize(bob.bot_position - glm::vec2{ g_data.camera_pos } - glm::vec2{ inp.cursor_pos });

			bob.bullets.push_back(b);
			bob.last_time_shot = t;
		}
	}
}

void bot_logic::shooting_bot(bot& bob, float t)
{
	for (int i=0; i<g_data.my_world.bots.size(); i++)
	{
		if (g_data.my_world.bots[i].alive == true and bob.team != g_data.my_world.bots[i].team)
		{
			glm::ivec2 bot_pos = glm::ivec2{ bob.chunk } - g_data.my_world.bots[i].chunk + glm::ivec2{ set.r_visible_area, set.r_visible_area };

			if (-1 < bot_pos.x and bot_pos.x < bob.size_visible_area and -1 < bot_pos.y and bot_pos.y < bob.size_visible_area )
			{
				if (bob.visible_area[bob.size_visible_area - bot_pos.x - 1][bob.size_visible_area - bot_pos.y - 1] == true)
				{
					if (bob.focusing_bot != -1)
					{
						if (glm::length(bob.bot_position - g_data.my_world.bots[i].bot_position) < glm::length(bob.bot_position - g_data.my_world.bots[bob.focusing_bot].bot_position))
						{
							bob.focusing_bot = i;
						}
					}
					else
					{
						bob.focusing_bot = i;
					}
				}

			}			
		}
	}
	if (bob.focusing_bot != -1 and (t - bob.last_time_shot) > set.time_between_shots)
	{
		bullet b;
		b.start_position = glm::ivec2{ bob.bot_position } + set.bot_size / 2 - g_data.bullet.center;
		b.current_position = b.start_position;
		b.direction_movement = -glm::normalize(bob.bot_position - g_data.my_world.bots[bob.focusing_bot].bot_position);

		g_data.my_world.u_bots.push_back(bob.chunk);
		g_data.my_world.u_bots.push_back(g_data.my_world.bots[bob.focusing_bot].chunk);
		bob.bullets.push_back(b);
		bob.last_time_shot = t;

		

		glm::vec2 v1, v2;
		v1 = bob.direction_viewing;
		v2 = g_data.my_world.bots[bob.focusing_bot].direction_viewing;
		if ((v1.x * v2.x + v1.y * v2.y) < 0)
		{
			/*std::cout << v1.x << " " << v1.y << std::endl;
			std::cout << v2.x << " " << v2.y << std::endl;
			std::cout << std::endl;*/
			bob.status = 1;
			
			glm::ivec2 world_size = g_data.my_world.get_size_world();
			for (int n = 0; n < world_size.x; n++)
			{
				for (int m = 0; m < world_size.y; m++)
				{
					glm::ivec2 p{ n, m };
					g_data.my_world.thermal_matrix_1_for_bots[n][m] = g_data.my_world.thermal_matrix_1_lite[n][m] - learn_func(g_data.my_world.bots[bob.focusing_bot].chunk, p, set.r_aggressive, set.e_aggressive);
				}
			}

			glm::ivec2 size_world = g_data.my_world.get_size_world();
			int h = set.thermal_map_min - 1;
			glm::ivec2 p;

			for (int i = -set.find_way_r; i <= set.find_way_r; i++)
			{
				for (int j = -set.find_way_r; j <= set.find_way_r; j++)
				{
					glm::ivec2 p_ch = bob.chunk + glm::ivec2{ i, j };
					if (p_ch.x > 0 and p_ch.x < size_world.x and
						p_ch.y > 0 and p_ch.y < size_world.y and g_data.my_world.passage_matrix[p_ch.x][p_ch.y] != '0')
					{
						int k = g_data.my_world.thermal_matrix_1_for_bots[p_ch.x][p_ch.y] + glm::length(glm::vec2{ i, j }) * set.find_way_e_increase + rand() % set.find_way_e_increase;
						if (k > h)
						{
							h = k;
							p = p_ch;
						}
					}
				}
			}
			

			/*for (int j = 0; j < world_size.y; j++)
			{
				for (int i = 0; i < world_size.x; i++)
				{
					std::cout << g_data.my_world.thermal_matrix_1_for_bots[j][i] << " ";
				}
				std::cout << std::endl;
			}*/

			bob.way_movement.clear();
			//std::cout << p.x << " " << p.y << std::endl;
			bob.way_movement = find_way(bob.chunk, p, g_data.my_world.thermal_matrix_1_lite);
		}
		else
		{
			bob.status = 2;

			glm::ivec2 world_size = g_data.my_world.get_size_world();
			for (int n = 0; n < world_size.x; n++)
			{
				for (int m = 0; m < world_size.y; m++)
				{
					glm::ivec2 p{ n, m };
					g_data.my_world.thermal_matrix_1_for_bots[n][m] = g_data.my_world.thermal_matrix_1_lite[n][m] + learn_func(g_data.my_world.bots[bob.focusing_bot].chunk, p, set.r_aggressive, set.e_aggressive);
				}
			}

			glm::ivec2 size_world = g_data.my_world.get_size_world();
			int h = set.thermal_map_min - 1;
			glm::ivec2 p;

			for (int i = -set.find_way_r; i <= set.find_way_r; i++)
			{
				for (int j = -set.find_way_r; j <= set.find_way_r; j++)
				{
					glm::ivec2 p_ch = bob.chunk + glm::ivec2{ i, j };
					if (p_ch.x > 0 and p_ch.x < size_world.x and
						p_ch.y > 0 and p_ch.y < size_world.y and g_data.my_world.passage_matrix[p_ch.x][p_ch.y] != '0')
					{
						int k = g_data.my_world.thermal_matrix_1_for_bots[p_ch.x][p_ch.y] + glm::length(glm::vec2{ i, j }) * set.find_way_e_increase + rand() % set.find_way_e_increase;
						if (k > h)
						{
							h = k;
							p = p_ch;
						}
					}
				}
			}


			/*for (int j = 0; j < world_size.y; j++)
			{
				for (int i = 0; i < world_size.x; i++)
				{
					std::cout << g_data.my_world.thermal_matrix_1_for_bots[j][i] << " ";
				}
				std::cout << std::endl;
			}*/

			bob.way_movement.clear();
			//std::cout << p.x << " " << p.y << std::endl;
			bob.way_movement = find_way(bob.chunk, p, g_data.my_world.thermal_matrix_1_lite);
		}
	}
}

void bot_logic::move_bullets(bot& bob, float alpha)
{
	for (auto& i : g_data.my_world.bots)
	{
		for (auto& j : i.bullets)
		{
			j.current_position += j.direction_movement * alpha * set.bullet_speed;
		}
	}
}

void bot_logic::check_bullets(bot& bob)
{
	//тут снар€ди €к≥ мають видалитис€
	std::set<int> d_elements;

	//перев≥рка к≥лькост≥ снар€д≥в
	if (bob.bullets.size() > set.n_ammo)
	{
		d_elements.insert(0);
	}

	//пошук в ст≥нах, простий алгоритм
	for (int i=0; i<bob.bullets.size(); i++)
	{
		if (g_data.my_world.passage_matrix[(int)(bob.bullets[i].current_position.x + g_data.bullet.center.x) / set.block_size.x][(int)(bob.bullets[i].current_position.y + g_data.bullet.center.y) / set.block_size.y] == '0')
		{
			d_elements.insert(i);
		}
	}
	
	//пошук пуль €к≥ попали в гравц€
	for (int i = 0; i < bob.bullets.size(); i++)
	{
		glm::vec2 bullet_b[4];
		bullet_b[0].x = bob.bullets[i].current_position.x;
		bullet_b[0].y = bob.bullets[i].current_position.y;
		bullet_b[1].x = bullet_b[0].x + g_data.bullet.size.x;
		bullet_b[1].y = bullet_b[0].y;
		bullet_b[2].x = bullet_b[0].x;
		bullet_b[2].y = bullet_b[0].y + g_data.bullet.size.y;
		bullet_b[3].x = bullet_b[1].x;
		bullet_b[3].y = bullet_b[2].y;

		for (int j=0; j<g_data.my_world.bots.size(); j++)
		{
			if (bob.team != g_data.my_world.bots[j].team and g_data.my_world.bots[j].alive == true)
			{
				if (abs(g_data.my_world.bots[j].bot_position.x - bullet_b[0].x) < set.block_size.x and abs(g_data.my_world.bots[j].bot_position.y - bullet_b[0].y) < set.block_size.y)
				{
					glm::vec2 bot_b[2];
					bot_b[0].x = g_data.my_world.bots[j].bot_position.x;
					bot_b[0].y = g_data.my_world.bots[j].bot_position.y;
					bot_b[1].x = g_data.my_world.bots[j].bot_position.x + set.bot_size.x;
					bot_b[1].y = g_data.my_world.bots[j].bot_position.y + set.bot_size.y;

					if (check_crossing(bot_b, bullet_b) == true)
					{
						bob.bullets[i].end_position = bob.bullets[i].current_position;
						g_data.my_world.u_bullets.emplace_back(bob.bullets[i]);

						d_elements.insert(i);
						g_data.my_world.bots[j].alive = false;
						bob.k_bots.emplace_back(j);

						break;
					}
				}
			}
		}
	}
	
	
	//видаленн€ пуль €к≥ в масив≥
	if (d_elements.size() == 0)
	{
		return;
	}
	else
	{
		std::set<int>::iterator elements_iterator = d_elements.begin();
		std::vector<bullet> n_bullets;
		for (int i = 0; i < bob.bullets.size(); i++)
		{
			if (elements_iterator != d_elements.end())
			{
				if (i == *elements_iterator)
				{
					elements_iterator++;
				}
				else
				{
					n_bullets.emplace_back(bob.bullets[i]);
				}
			}
			else
			{
				n_bullets.emplace_back(bob.bullets[i]);
			}
		}

		std::swap(n_bullets, bob.bullets);
	}
}

void bot_logic::check_crossing_bot(bot& bob)
{
	glm::vec2 p[4];
	p[0] = bob.bot_position;
	p[1] = bob.bot_position + glm::vec2{ set.bot_size.x, 0 };
	p[2] = bob.bot_position + glm::vec2{ set.bot_size };
	p[3] = bob.bot_position + glm::vec2{ 0, set.bot_size.y };

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			glm::ivec2 c;
			c.x = i + bob.chunk.x;
			c.y = j + bob.chunk.y;

			if (0 <= c.x and c.x < g_data.my_world.get_size_world().x and 0 <= c.y and c.y < g_data.my_world.get_size_world().y)
			{
				if (g_data.my_world.passage_matrix[c.x][c.y] == '0')
				{
					glm::vec2 s[2];
					
					s[0].x = c.x * set.block_size.x;
					s[0].y = c.y * set.block_size.y;
					s[1].x = c.x * set.block_size.x + set.block_size.x;
					s[1].y = c.y * set.block_size.y + set.block_size.y;

					for (int k = 0; k < 4; k++)
					{
						if (check_inside_point(s, p[k]) == true)
						{
							bob.ch_cros[k] = true;
						}
					}
				}
			}
		}
	}

	if (bob.ch_cros[0] == true and bob.ch_cros[1] == true and bob.ch_cros[3] == true)
	{
		bob.bot_position.y = bob.chunk.y * set.block_size.y;
		bob.bot_position.x = bob.chunk.x * set.block_size.x;
	}
	else if (bob.ch_cros[0] == true and bob.ch_cros[1] == true and bob.ch_cros[2] == true)
	{
		bob.bot_position.y = bob.chunk.y * set.block_size.y;
		bob.bot_position.x = (bob.chunk.x + 1) * set.block_size.x - set.bot_size.x;
	}
	else if (bob.ch_cros[1] == true and bob.ch_cros[2] == true and bob.ch_cros[3] == true)
	{
		bob.bot_position.y = (bob.chunk.y + 1) * set.block_size.y - set.bot_size.y;
		bob.bot_position.x = (bob.chunk.x + 1) * set.block_size.x - set.bot_size.x;
	}
	else if (bob.ch_cros[2] == true and bob.ch_cros[3] == true and bob.ch_cros[0] == true)
	{
		bob.bot_position.x = bob.chunk.x * set.block_size.x;
		bob.bot_position.y = (bob.chunk.y + 1) * set.block_size.y - set.bot_size.y;
	}
	else if (bob.ch_cros[0] == true and bob.ch_cros[1] == true)
	{
		bob.bot_position.y = bob.chunk.y * set.block_size.y;
	}
	else if (bob.ch_cros[1] == true and bob.ch_cros[2] == true)
	{
		bob.bot_position.x = (bob.chunk.x + 1) * set.block_size.x - set.bot_size.x;
	}
	else if (bob.ch_cros[2] == true and bob.ch_cros[3] == true)
	{
		bob.bot_position.y = (bob.chunk.y + 1) * set.block_size.y - set.bot_size.y;
	}
	else if (bob.ch_cros[0] == true and bob.ch_cros[3] == true)
	{
		bob.bot_position.x = bob.chunk.x * set.block_size.x;
	}
	else if (bob.ch_cros[0] == true)
	{
		glm::vec2 d;

		d.x = set.block_size.x - bob.bot_position.x + bob.chunk.x * set.block_size.x;
		d.y = set.block_size.y - bob.bot_position.y + bob.chunk.y * set.block_size.y;

		if (d.x > d.y)
		{
			bob.bot_position.x = bob.chunk.x * set.block_size.x;
		}
		else
		{
			bob.bot_position.y = bob.chunk.y * set.block_size.y;
		}

		if (abs(bob.direction_movement.x) > abs(bob.direction_movement.y))
		{
			bob.bot_position.y += 1;
		}
		else
		{
			bob.bot_position.x += 1;
		}
	}
	else if (bob.ch_cros[1] == true)
	{
		glm::vec2 d;
		d.x = bob.bot_position.x - bob.chunk.x * set.block_size.x;
		d.y = set.block_size.y - bob.bot_position.y + bob.chunk.y * set.block_size.y;

		if (d.x > d.y)
		{
			bob.bot_position.x = (bob.chunk.x + 1) * set.block_size.x - set.bot_size.x;
		}
		else
		{
			bob.bot_position.y = bob.chunk.y * set.block_size.y;
		}

		if (abs(bob.direction_movement.x) > abs(bob.direction_movement.y))
		{
			bob.bot_position.y += 1;
		}
		else
		{
			bob.bot_position.x -= 1;
		}
	}
	else if (bob.ch_cros[2] == true)
	{
		glm::vec2 d;
		d.x = bob.bot_position.x - bob.chunk.x * set.block_size.x;
		d.y = bob.bot_position.y - bob.chunk.y * set.block_size.y;

		if (d.x > d.y)
		{
			bob.bot_position.x = (bob.chunk.x + 1) * set.block_size.x - set.bot_size.x;
		}
		else
		{
			bob.bot_position.y = (bob.chunk.y + 1) * set.block_size.y - set.bot_size.y;
		}

		if (abs(bob.direction_movement.x) > abs(bob.direction_movement.y))
		{
			bob.bot_position.y -= 1;
		}
		else
		{
			bob.bot_position.x -= 1;
		}
	}
	else if (bob.ch_cros[3] == true)
	{
		glm::vec2 d;
		d.x = set.block_size.x - bob.bot_position.x + bob.chunk.x * set.block_size.x;
		d.y = bob.bot_position.y - bob.chunk.y * set.block_size.y;

		if (d.x > d.y)
		{
			bob.bot_position.x = bob.chunk.x * set.block_size.x;
		}
		else
		{
			bob.bot_position.y = (bob.chunk.y + 1) * set.block_size.y - set.bot_size.y;
		}

		if (abs(bob.direction_movement.x) > abs(bob.direction_movement.y))
		{
			bob.bot_position.y -= 1;
		}
		else
		{
			bob.bot_position.x += 1;
		}
	}

	/*for (int i = 0; i < 4; i++)
	{
		if (bob.ch_cros[i] == true)
		{
			std::cout << i << " ";
		}		
	}
	std::cout << std::endl;*/
}

void bot_logic::m_bot_movement(bot& bob, float alpha)
{
	glm::ivec2 block_pos = bob.way_movement.front();
	glm::ivec2 mini_task;

	int h = set.thermal_map_min - 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_data.my_world.thermal_matrix_1[block_pos.x * 4 + i][block_pos.y * 4 + j] > h)
			{
				mini_task = glm::ivec2{ i, j };
			}
		}
	}

	glm::vec2 p_mini_task = glm::vec2{ (block_pos.x * 4 + mini_task.x) * set.thermal_block_size.x, (block_pos.y * 4 + mini_task.y) * set.thermal_block_size.y };
	
	//glm::vec2 p_mini_task = glm::vec2{ block_pos.x * set.block_size.x + block_pos.x / 2, block_pos.y * set.block_size.y + block_pos.y / 2 };

	bob.direction_movement = glm::normalize(p_mini_task - bob.bot_position - glm::vec2{ set.bot_size / 2 });
	if (glm::length(bob.direction_movement) != 0)
	{
		bob.bot_position += bob.direction_movement * alpha * set.bot_speed;
	}
}

void bot_logic::check_m_bot(bot& bob)
{
	bool b = false;
	if (bob.chunk == bob.way_movement.front())
	{
		b = true;
	}

	if (b == true)
	{
		bob.way_movement.pop_front();
	}
}
