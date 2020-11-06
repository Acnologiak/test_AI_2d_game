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
	my_world.black = createSprite("sprites/black.png");

	if (my_world.load_world("worlds/test.txt") == false)
	{
		return false;
	}

	//задання позиції гравців
	for (int i = 0; i < set.world_size.x; i++)
	{
		for (int j = 0; j < set.world_size.y; j++)
		{
			if (my_world.passage_matrix[j][i] == 2)
			{
				creature c;
				c.spr.load_sprite("sprites/team1.png");
				c.position.x = i * set.block_size.x + set.block_size.x / 2 - c.spr.center.x;
				c.position.y = j * set.block_size.y + set.block_size.y / 2 - c.spr.center.y;
				my_world.team1.emplace_back(c);


				//my_world.pl.position.x = i * set.block_size.x + set.block_size.x / 2 - my_world.pl.spr.center.x;
				//my_world.pl.position.y = j * set.block_size.y + set.block_size.y / 2 - my_world.pl.spr.center.y;
			}
			else if (my_world.passage_matrix[j][i] == 3)
			{
				creature c;
				c.spr.load_sprite("sprites/team2.png");
				c.position.x = i * set.block_size.x + set.block_size.x / 2 - c.spr.center.x;
				c.position.y = j * set.block_size.y + set.block_size.y / 2 - c.spr.center.y;
				my_world.team1.emplace_back(c);
			}
		}
	}
	my_world.pl = &(my_world.team1[0]);



	return true;
}

void MyFramework::Close()
{
	destroySprite(my_world.x);
}

bool MyFramework::Tick()
{
	update_alpha();
	my_world.update_player_position(alpha);
	my_world.update_camera_position();
	my_world.pl->update_visible_area();

	draw_world();
	draw_players();
	draw_fog();
	
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

void MyFramework::draw_players()
{
	for (const auto& i : my_world.team1)
	{
		drawSprite(i.spr.texture, i.position.x + my_world.camera_position.x, i.position.y + my_world.camera_position.y);
	}
	for (const auto& i : my_world.team2)
	{
		drawSprite(i.spr.texture, i.position.x + my_world.camera_position.x, i.position.y + my_world.camera_position.y);
	}
}

void MyFramework::draw_world()
{
	if (set.fog == true)
	{
		for (int i = 0; i < set.world_size.x; i++)
		{
			for (int j = 0; j < set.world_size.y; j++)
			{
				if (my_world.pl->visible_area[i][j] == true)
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
		}
	}
	else
	{
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
	}
}

void MyFramework::draw_fog()
{
	if (set.fog == true)
	{
		for (int i = 0; i < set.world_size.x; i++)
		{
			for (int j = 0; j < set.world_size.y; j++)
			{
				if (my_world.pl->visible_area[i][j] == false)
				{
					drawSprite(my_world.black, i * set.block_size.x + my_world.camera_position.x, j * set.block_size.y + my_world.camera_position.y);
				}
			}
		}
	}
}
