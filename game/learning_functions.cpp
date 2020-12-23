#include "learning_functions.h"

int learn_func(glm::ivec2& p_center, glm::ivec2& p_ch, int r_learning, int e_learning)
{
	int delta = 0;
	glm::vec2 p_r = p_center - p_ch;

	float l = glm::length(p_r);
	if (l <= r_learning)
	{
		delta = ((float)r_learning - l) / (float)r_learning * (float)r_learning;
	}

	return delta;
}