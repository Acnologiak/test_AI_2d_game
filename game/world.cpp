#include "world.h"

#include <fstream>

world::world()
{

}

bool world::load_world(std::string n_world)
{
	std::string s;

	name_world = n_world;
	n_world = "worlds/" + name_world + "/map.txt";
	std::ifstream file(n_world);
	if (!file.is_open())
	{
		return false;
	}

	//зчитання розміру світу
	file >> s;
	size_world.x = atoi(s.c_str());
	file >> s;
	size_world.y = atoi(s.c_str());

	//створення матриць для заповнення світу
	passage_matrix = new unsigned char* [size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		passage_matrix[i] = new unsigned char[size_world.y];
	}
	world_matrix = new unsigned  char* [size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		world_matrix[i] = new unsigned  char[size_world.y];
	}

	//зчитання світу
	char ch[1];
	for (int i = 0; i < size_world.y; i++)
	{
		file >> s;
		
		for (int j = 0; j < size_world.x; j++)
		{
			passage_matrix[j][i] = (char)s[j];
		}
	}
	for (int i = 0; i < size_world.y; i++)
	{
		file >> s;
		for (int j = 0; j < size_world.x; j++)
		{
			world_matrix[j][i] = (char)s[j];
		}
	}
	file.close();


	//створення теплової матриці переміщення
	size_thermal_matrix_1 = size_world * 4;
	thermal_matrix_1 = new int* [size_thermal_matrix_1.x];
	for (int i = 0; i < size_thermal_matrix_1.x; i++)
	{
		thermal_matrix_1[i] = new int[size_thermal_matrix_1.y];
	}
	//створення спрощеної теплової матриці переміщення
	thermal_matrix_1_lite = new int* [size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		thermal_matrix_1_lite[i] = new int[size_world.y];
	}

	//зчитаннян теплової матриці руху
	n_world = "worlds/" + name_world + "/thermal_map_1.txt";
	file.open(n_world);
	if (!file.is_open())
	{
		return false;
	}
	for (int j = 0; j < size_thermal_matrix_1.y; j++)
	{
		for (int i = 0; i < size_thermal_matrix_1.x; i++)
		{
			file >> s;
			thermal_matrix_1[i][j] = atoi(s.c_str());
		}
	}

	//створення матриці для ботів
	thermal_matrix_1_for_bots = new int* [size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		thermal_matrix_1_for_bots[i] = new int[size_world.y];
	}


	//зчитаннян теплової матриці для уваги
	thermal_matrix_2 = new int* [size_world.x];
	for (int i = 0; i < size_world.x; i++)
	{
		thermal_matrix_2[i] = new int[size_world.y];
	}
	file.close();

	n_world = "worlds/" + name_world + "/thermal_map_2.txt";
	file.open(n_world);
	if (!file.is_open())
	{
		return false;
	}
	for (int j = 0; j < size_world.y; j++)
	{
		for (int i = 0; i < size_world.x; i++)
		{
			file >> s;
			thermal_matrix_2[i][j] = atoi(s.c_str());
		}
	}
	file.close();

	status = true;
	return true;
}

void world::spawn_bots()
{
	bots.clear();

	int t = 0;
	for (int i = 0; i < size_world.x; i++)
	{
		for (int j = 0; j < size_world.y; j++)
		{
			if (passage_matrix[i][j] == '2')
			{
				bot vova;

				vova.bot_position.x = i * set.block_size.x + (set.block_size.x - set.bot_size.x) / 2;
				vova.bot_position.y = j * set.block_size.y + (set.block_size.y - set.bot_size.y) / 2;
				vova.team = t;

				int size_visible_area = set.r_visible_area * 2 + 1;
				vova.size_visible_area = size_visible_area;
				for (int i = 0; i < vova.size_visible_area; i++)
				{
					std::vector<bool> b;
					for (int j = 0; j < vova.size_visible_area; j++)
					{
						b.emplace_back(false);
					}
					vova.visible_area.emplace_back(b);
				}

				bots.emplace_back(vova);
				t++;
			}
		}
	}
}

void world::save_thermal_matrix_1()
{
	std::string path = "worlds/" + name_world + "/thermal_map_1.txt";
	std::ofstream file(path);

	for (int j = 0; j < size_thermal_matrix_1.y; j++)
	{
		for (int i = 0; i < size_thermal_matrix_1.x; i++)
		{
			file << (int)thermal_matrix_1[i][j] << " ";
		}
		file << std::endl;
	}

	file.close();
}

void world::save_thermal_matrix_2()
{
	std::string path = "worlds/" + name_world + "/thermal_map_2.txt";
	std::ofstream file(path);

	for (int j = 0; j < size_world.y; j++)
	{
		for (int i = 0; i < size_world.x; i++)
		{
			file << (int)thermal_matrix_2[i][j] << " ";
		}
		file << std::endl;
	}

	file.close();
}

world::~world()
{
	save_thermal_matrix_1();
	save_thermal_matrix_2();

	if (status == true)
	{
		for (int i = 0; i < size_world.x; i++)
		{
			delete[] passage_matrix[i];
			delete[] world_matrix[i];
			delete[] thermal_matrix_1_lite[i];
			delete[] thermal_matrix_2[i];
			delete[] thermal_matrix_1_for_bots[i];
		}
		delete passage_matrix;
		delete world_matrix;
		delete[] thermal_matrix_1_lite;
		delete[] thermal_matrix_2;
		delete[] thermal_matrix_1_for_bots;

		for (int i = 0; i < size_thermal_matrix_1.x; i++)
		{
			delete[] thermal_matrix_1[i];
		}
		delete thermal_matrix_1;
	}
}
