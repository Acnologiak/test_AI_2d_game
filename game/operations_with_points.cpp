#include "operations_with_points.h"

bool check_inside_point(glm::vec2* spr, glm::vec2& p)
{
    if (spr[0].x <= p.x and p.x <= spr[1].x and spr[0].y <= p.y and p.y <= spr[1].y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_crossing(glm::vec2* obj_1, glm::vec2* obj_2)
{
    for (int k = 0; k < 4; k++)
    {
        if (check_inside_point(obj_1, obj_2[k]) == true)
        {
            return true;
        }
    }

    return false;
}
