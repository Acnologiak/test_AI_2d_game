#pragma once

#include "glm/glm.hpp"
#include "my_sprite.h"

//функція перевірки чи точка знаходиться всередині об'єкту (2, 1) точки
bool check_inside_point(glm::vec2* spr, glm::vec2& p);

//функція перевірки перетину 2 спрайтів (2, 4) точки
bool check_crossing(glm::vec2* obj_1, glm::vec2* obj_2);