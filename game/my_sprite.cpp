#include "my_sprite.h"


void my_sprite::load_sprite(std::string s)
{
	s = "sprites/" + s;
	texture = createSprite(s.c_str());
	getSpriteSize(texture, size.x, size.y);

	box_template[0] = glm::ivec2{ 0, 0 };
	box_template[1] = glm::ivec2{ size.x, 0 };
	box_template[2] = glm::ivec2{ size.x, size.y };
	box_template[3] = glm::ivec2{ 0, size.y };

	center = { size.x / 2, size.y / 2 };

	status = true;
}