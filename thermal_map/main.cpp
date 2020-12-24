#include <fstream>
#include <iostream>

#include "glm/glm.hpp"


void create_thermal_map()
{
	glm::ivec2 size{ 64, 64 };

	char** map;
	map = new char* [size.x];
	for (int i = 0; i < size.x; i++)
	{
		map[i] = new char[size.y];
		for (int j = 0; j < size.y; j++)
		{
			map[i][j] = rand()%16-8;
		}
	}

	std::ofstream file("thermal_map.txt");

	for (int j = 0; j < size.y; j++)
	{
		for (int i = 0; i < size.x; i++)
		{
			file << (int)map[i][j] << " ";
		}
		file << std::endl;
	}

	file.close();
}



int main()
{

	create_thermal_map();



	return 0;
}