#include "utilities.h"

#include "world.h"

void n_normalize(glm::vec2& p)
{
	float f = sqrt(p.x * p.x + p.y * p.y);
	if (f != 0)
	{
		p.x = p.x / f;
		p.y = p.y / f;
	}
}


bool check_crossing(my_sprite sprite_1, glm::ivec2 spr_1_pos, my_sprite sprite_2, glm::ivec2 spr_2_pos)
{
	for (int i = 0; i < 4; i++)
	{
		sprite_1.box_template[i] += spr_1_pos;
		sprite_2.box_template[i] += spr_2_pos;
	}

	for (int i = 0; i < 4; i++)
	{
		if (sprite_1.box_template[0].x <= sprite_2.box_template[i].x and sprite_1.box_template[2].x >= sprite_2.box_template[i].x
			and sprite_1.box_template[0].y <= sprite_2.box_template[i].y and sprite_1.box_template[2].y >= sprite_2.box_template[i].y)
		{
			return true;
		}
		if (sprite_2.box_template[0].x <= sprite_1.box_template[i].x and sprite_2.box_template[2].x >= sprite_1.box_template[i].x
			and sprite_2.box_template[0].y <= sprite_1.box_template[i].y and sprite_2.box_template[2].y >= sprite_1.box_template[i].y)
		{
			return true;
		}
	}

	return false;
}