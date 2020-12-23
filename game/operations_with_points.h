#pragma once

#include "glm/glm.hpp"
#include "my_sprite.h"

//������� �������� �� ����� ����������� �������� ��'���� (2, 1) �����
bool check_inside_point(glm::vec2* spr, glm::vec2& p);

//������� �������� �������� 2 ������� (2, 4) �����
bool check_crossing(glm::vec2* obj_1, glm::vec2* obj_2);