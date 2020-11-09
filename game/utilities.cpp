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


int check_crossing(my_sprite &sprite_1, glm::ivec2 spr_1_pos, my_sprite &sprite_2, glm::ivec2 spr_2_pos)
{
	bool r[4];

	glm::ivec2 box_template_spr_1[4];
	glm::ivec2 box_template_spr_2[4];
	for (int i = 0; i < 4; i++)
	{
		box_template_spr_1[i] = sprite_1.box_template[i] + spr_1_pos;
		box_template_spr_2[i] = sprite_2.box_template[i] + spr_2_pos;
	}
	
	for (int i = 0; i < 4; i++)
	{
		if (box_template_spr_1[0].x < box_template_spr_2[i].x < box_template_spr_1[1].x and
			box_template_spr_1[0].y < box_template_spr_2[i].y < box_template_spr_1[3].y)
		{
			std::cout << "!";
			return i;
			
		}
	}


	return -1;
}