#pragma once

#include "glm/glm.hpp"


class input
{
public:
	static input& instance();

	bool keyboard_up = false;
	bool keyboard_left = false;
	bool keyboard_right = false;
	bool keyboard_down = false;

	bool mouse_left = false;
	bool mouse_middle = false;
	bool mouse_right = false;

	glm::ivec2 cursor_pos;
	glm::ivec2 relative;
private:
	input() = default;
};