#pragma once

#include "glm/glm.hpp"

class my_sprite;


//функція нормалізування
void n_normalize(glm::vec2& p);

//функція перевірки перетину 2 спрайтів
bool check_crossing(my_sprite& sprite_1, glm::ivec2 spr_1_pos, my_sprite& sprite_2, glm::ivec2 spr_2_pos);