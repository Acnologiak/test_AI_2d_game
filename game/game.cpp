#include "game.h"


void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = set.window_size.x;
	height = set.window_size.y;

	fullscreen = set.fullscreen;
}

bool MyFramework::Init()
{
	if (my_world.load_world("worlds/test.txt") == false)
	{
		return false;
	}
	

	return true;
}

void MyFramework::Close()
{
	
}

bool MyFramework::Tick()
{
	
	
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	inp.cursor_pos.x = x;
	inp.cursor_pos.y = y;

	inp.relative.x = xrelative;
	inp.relative.y = yrelative;
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (isReleased == false)
	{
		if (button == FRMouseButton::LEFT)
		{
			inp.mouse_left = true;
		}
		else if (button == FRMouseButton::MIDDLE)
		{
			inp.mouse_middle = true;
		}
		else if (button == FRMouseButton::RIGHT)
		{
			inp.mouse_right = true;
		}
	}
	else
	{
		if (button == FRMouseButton::LEFT)
		{
			inp.mouse_left = false;
		}
		else if (button == FRMouseButton::MIDDLE)
		{
			inp.mouse_middle = false;
		}
		else if (button == FRMouseButton::RIGHT)
		{
			inp.mouse_right = false;
		}
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	if (k == FRKey::UP)
	{
		inp.keyboard_up = true;
	}
	if (k == FRKey::DOWN)
	{
		inp.keyboard_down = true;
	}
	if (k == FRKey::LEFT)
	{
		inp.keyboard_left = true;
	}
	if (k == FRKey::RIGHT)
	{
		inp.keyboard_right = true;
	}
}

void MyFramework::onKeyReleased(FRKey k)
{
	if (k == FRKey::UP)
	{
		inp.keyboard_up = false;
	}
	if (k == FRKey::DOWN)
	{
		inp.keyboard_down = false;
	}
	if (k == FRKey::LEFT)
	{
		inp.keyboard_left = false;
	}
	if (k == FRKey::RIGHT)
	{
		inp.keyboard_right = false;
	}
}

void MyFramework::update_alpha()
{
	unsigned int current_time = getTickCount();
	delta_time = current_time - last_time;
	last_time = current_time;

	//fps = 1000 / (float)delta_time;
	//добавити обмеження fps

	alpha = (float)delta_time / 1000;
}
