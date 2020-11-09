#include "utilities.h"

#include "world.h"

#include <iostream>

void n_normalize(glm::vec2& p)
{
	float f = sqrt(p.x * p.x + p.y * p.y);
	if (f != 0)
	{
		p.x = p.x / f;
		p.y = p.y / f;
	}
}


bool check_crossing(my_sprite& sprite_1, glm::ivec2 spr_1_pos, my_sprite& sprite_2, glm::ivec2 spr_2_pos)
{
	/*for (int i = 0; i < 4; i++)
	{
		std::cout << sprite_1.box_template[i].x << " " << sprite_1.box_template[i].y << std::endl;
	}
	std::cout << std::endl;*/

	glm::ivec2 box_template_spr_1[4];
	glm::ivec2 box_template_spr_2[4];
	for (int i = 0; i < 4; i++)
	{
		box_template_spr_1[i] = sprite_1.box_template[i] + spr_1_pos;
		box_template_spr_2[i] = sprite_2.box_template[i] + spr_2_pos;
	}

	for (int i = 0; i < 4; i++)
	{
		if (box_template_spr_1[0].x <= box_template_spr_2[i].x and box_template_spr_1[2].x >= box_template_spr_2[i].x
			and box_template_spr_1[0].y <= box_template_spr_2[i].y and box_template_spr_1[2].y >= box_template_spr_2[i].y)
		{
			return true;
		}
		if (box_template_spr_2[0].x <= box_template_spr_1[i].x and box_template_spr_2[2].x >= box_template_spr_1[i].x
			and box_template_spr_2[0].y <= box_template_spr_1[i].y and box_template_spr_2[2].y >= box_template_spr_1[i].y)
		{
			return true;
		}
	}

	/*for (int i = 0; i < 4; i++)
	{
		std::cout << box_template_spr_1[i].x << " " << box_template_spr_1[i].y << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << box_template_spr_2[i].x << " " << box_template_spr_2[i].y << std::endl;
	}
	std::cout << std::endl;*/

	//system("pause");

	return false;
}