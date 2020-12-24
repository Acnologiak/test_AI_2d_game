#include "game_data.h"


game_data& game_data::instance()
{
	static game_data instance;
	return instance;
}

void game_data::update_thermal_matrix_1()
{
	glm::ivec2 t_m_1_size = my_world.get_size_thermal_matrix_1();
	for (auto& i : my_world.u_bullets)
	{
		glm::ivec2 start_pos{ i.start_position.x / set.thermal_block_size.x,  i.start_position.y / set.thermal_block_size.y };
		glm::ivec2 end_pos{ i.end_position.x / set.thermal_block_size.x,  i.end_position.x / set.thermal_block_size.y };
		for (int n = 0; n < t_m_1_size.x; n++)
		{
			for (int m = 0; m < t_m_1_size.y; m++)
			{
				glm::ivec2 p{ n, m };
				my_world.thermal_matrix_1[n][m] += learn_func(start_pos, p, set.r_learning, set.e_learning);
				my_world.thermal_matrix_1[n][m] -= learn_func(end_pos, p, set.r_learning, set.e_learning);
			}
		}
	}
	my_world.u_bullets.clear();

	normalize_update_thermal_matrix_1();
}

void game_data::normalize_update_thermal_matrix_1()
{
	glm::ivec2 t_m_1_size = my_world.get_size_thermal_matrix_1();
	glm::ivec2 t_m_1_size_lite = my_world.get_size_world();
	int max = my_world.thermal_matrix_1[0][0];
	int min = my_world.thermal_matrix_1[0][0];

	for (int n = 0; n < t_m_1_size.x; n++)
	{
		for (int m = 0; m < t_m_1_size.y; m++)
		{
			if (my_world.thermal_matrix_1[n][m] > max)
			{
				max = my_world.thermal_matrix_1[n][m];
			}
			if (my_world.thermal_matrix_1[n][m] < min)
			{
				min = my_world.thermal_matrix_1[n][m];
			}
		}
	}

	int landslide = (max + min) / 2;
	for (int n = 0; n < t_m_1_size.x; n++)
	{
		for (int m = 0; m < t_m_1_size.y; m++)
		{
			my_world.thermal_matrix_1[n][m] -= landslide;
		}
	}

	float e = (float)(max - min) / (float)(set.thermal_map_max - set.thermal_map_min);
	for (int n = 0; n < t_m_1_size.x; n++)
	{
		for (int m = 0; m < t_m_1_size.y; m++)
		{
			my_world.thermal_matrix_1[n][m] = (float)my_world.thermal_matrix_1[n][m] / e;
		}
	}

	//оновлення спрощеної теплової карти для руху
	for (int i = 0; i < t_m_1_size_lite.x; i++)
	{
		for (int j = 0; j < t_m_1_size_lite.y; j++)
		{
			int sum = 0;
			for (int n = 0; n < 4; n++)
			{
				for (int m = 0; m < 4; m++)
				{
					sum += my_world.thermal_matrix_1[i * 4 + n][j * 4 + m];
				}
			}
			sum /= 16;
			my_world.thermal_matrix_1_lite[i][j] = sum;
		}
	}

	/*for (int j = 0; j < t_m_1_size.y; j++)
	{
		for (int i = 0; i < t_m_1_size.x; i++)
		{
			std::cout << my_world.thermal_matrix_1[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	glm::ivec2 size_world = my_world.get_size_world();
}

void game_data::update_thermal_matrix_2()
{
	glm::ivec2 t_m_1_size = my_world.get_size_world();
	for (auto& i : my_world.u_bots)
	{
		for (int n = 0; n < t_m_1_size.x; n++)
		{
			for (int m = 0; m < t_m_1_size.y; m++)
			{
				glm::ivec2 p{ n, m };
				my_world.thermal_matrix_2[n][m] += learn_func(i, p, set.r_direction_viewing_learning, set.e_direction_viewing_learning);
			}
		}
	}
	my_world.u_bots.clear();

	normalize_update_thermal_matrix_2();
}

void game_data::normalize_update_thermal_matrix_2()
{
	glm::ivec2 t_m_2_size = my_world.get_size_world();
	int max = my_world.thermal_matrix_2[0][0];
	int min = my_world.thermal_matrix_2[0][0];


	for (int n = 0; n < t_m_2_size.x; n++)
	{
		for (int m = 0; m < t_m_2_size.y; m++)
		{
			if (my_world.thermal_matrix_2[n][m] > max)
			{
				max = my_world.thermal_matrix_2[n][m];
			}
			if (my_world.thermal_matrix_2[n][m] < min)
			{
				min = my_world.thermal_matrix_2[n][m];
			}
		}
	}

	int landslide = (max + min) / 2;
	for (int n = 0; n < t_m_2_size.x; n++)
	{
		for (int m = 0; m < t_m_2_size.y; m++)
		{
			my_world.thermal_matrix_2[n][m] -= landslide;
		}
	}

	float e = (float)(max - min) / (float)(set.thermal_map_max - set.thermal_map_min);
	for (int n = 0; n < t_m_2_size.x; n++)
	{
		for (int m = 0; m < t_m_2_size.y; m++)
		{
			my_world.thermal_matrix_2[n][m] = (float)my_world.thermal_matrix_2[n][m] / e;
		}
	}
}
