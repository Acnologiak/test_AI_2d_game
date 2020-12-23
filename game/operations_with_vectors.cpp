#include "operations_with_vectors.h"

void n_normalize(glm::vec2& p)
{
	float f = sqrt(p.x * p.x + p.y * p.y);
	if (f != 0)
	{
		p.x = p.x / f;
		p.y = p.y / f;
	}
}
