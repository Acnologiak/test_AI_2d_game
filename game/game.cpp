#include "game.h"

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = set.window_size.x;
	height = set.window_size.y;
	fullscreen = set.fullscreen;
}

bool MyFramework::Init()
{
	my_world.x = createSprite("sprites/0.png");
	my_world.y = createSprite("sprites/1.png");
	my_world.pl.spr.load_sprite("sprites/player.png");

	if (my_world.load_world("worlds/test.txt") == false)
	{
		return false;
	}

	my_world.pl.position = glm::vec2{ 0, 0 };

	my_world.world_matrix = new char* [set.world_size.x];
	for (int i = 0; i < set.world_size.x; i++)
	{
		my_world.world_matrix[i] = new char[set.world_size.y];
		for (int j = 0; j < set.world_size.y; j++)
		{
			if (i == 0 or j == 0 or i == set.world_size.x - 1 or j == set.world_size.y - 1)
			{
				my_world.world_matrix[i][j] = 1;
			}
			else
			{
				my_world.world_matrix[i][j] = 0;
			}
		}
	}

	return true;
}

void MyFramework::Close()
{
	destroySprite(my_world.x);
}

bool MyFramework::Tick()
{
	update_alpha();
	my_world.pl.update_player_position(alpha);
	my_world.update_camera_position();

	for (int i = 0; i < set.world_size.x; i++)
	{
		for (int j = 0; j < set.world_size.y; j++)
		{
			if (my_world.world_matrix[i][j] == 1)
			{
				drawSprite(my_world.y, i * set.block_size.x + my_world.camera_position.x, j * set.block_size.y + my_world.camera_position.y);
			}
			else
			{
				drawSprite(my_world.x, i * set.block_size.x + my_world.camera_position.x, j * set.block_size.y + my_world.camera_position.y);
			}
		}
	}
	drawSprite(my_world.pl.spr.texture, my_world.pl.position.x + my_world.camera_position.x, my_world.pl.position.y + +my_world.camera_position.y);
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
