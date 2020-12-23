#pragma once

#include "glm/glm.hpp"


class settings
{
public:
	static settings& instance();

	//режим глядача
	bool spectator_mode{ true };
	// теплова карта
	bool thermal_map{ false };
	//номер бота для старту гри
	int bot_number_for_game{ 0 };
	//швидкість камери
	float cam_speed{ 1000 };

	//розмір вікна
	glm::ivec2 window_size{ 1280, 720 };
	//повноекранний режим
	bool fullscreen{ false };

	//розмір блоку
	glm::ivec2 block_size{ 64, 64 };
	//розмір блоку теплової карти
	glm::ivec2 thermal_block_size{ 16, 16 };
	//розмір бота
	glm::ivec2 bot_size{ 32, 32 };
	//швидкість бота
	float bot_speed{150};


	//кількість снарядів
	unsigned int n_ammo{ 5 };
	//швидкість снаряда
	float bullet_speed{ 150 };
	//мінімальний час між вистрілами
	unsigned int time_between_shots{ 500 };

	//радіус видимості
	int r_visible_area{ 8 };
	//коефіціент зростання для пошуку шляху
	int find_direction_viewing_e_increase{ 1 };
	//радіус навчання для переміщення
	int r_direction_viewing_learning{ 5 };
	//коефіціент навчання для переміщення
	int e_direction_viewing_learning{ 20 };

	//радіус навчання для переміщення
	int r_learning{ 10 };
	//коефіціент навчання для переміщення
	int e_learning{ 10 };
	//максимум теплової карти 
	int thermal_map_max{ 128 };
	//мінімум теплової карти 
	int thermal_map_min{ -128 };

	//похибка при пошуці оптимальної точки призначення
	int error_destination{ 16 };
	//радіус пошуку потимальної точки
	int find_way_r{ 10 };
	//коефіціент зростання для пошуку шляху
	int find_way_e_increase{ 1 };
	//коефіціент для алгоритму пошуку шляху
	float find_way_z{ 100 };

	//коефіціент агресивності
	int e_aggressive{ 100 };
	//радіус агресивності
	int r_aggressive{ 3 };
private:
	settings() = default;
};

