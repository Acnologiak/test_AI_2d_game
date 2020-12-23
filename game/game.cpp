#include "game.h"


void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = set.window_size.x;
    height = set.window_size.y;
    fullscreen = set.fullscreen;
}

bool MyFramework::Init()
{
	g_data.my_world.load_world("1");
	if (g_data.my_world.get_status() == false)
	{
		return false;
	}
	g_data.my_world.spawn_bots();
	g_data.update_thermal_matrix_1();

	g_data.block_0.load_sprite("0.png");
	g_data.block_1.load_sprite("1.png");
	g_data.team_1.load_sprite("team1.png");
	g_data.bullet.load_sprite("bullet.png");

	for (int i = 0; i < 64; i++)
	{
		std::string path;
		path += "thermal blocks/" + std::to_string(i) + ".jpg";
		g_data.thermal_blocks[i].load_sprite(path);
	}

	restart_game();

    return true;
}

void MyFramework::Close()
{
}

bool MyFramework::Tick()
{
	//кінець гри?
	if (check_end_game() == true)
	{
		restart_game();
	}

	//оновлення позиції камери
	if (set.spectator_mode == true)
	{
		w_rendering.update_camera_pos_spectator(alpha);
	}
	else
	{
		w_rendering.update_camera_pos_pl();
	}

	//операції з ботом
	move_bots(alpha);
	shooting(alpha);
	b_logic.check_crossing_bots();
	//відображення світу
	if (set.thermal_map == true)
	{
		w_rendering.draw_thermal_blocks();
	}
	else
	{
		w_rendering.draw_blocks();
	}
	w_rendering.draw_bots();
	w_rendering.draw_bullets();

	//оновлення альфа
	update_alpha();

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

	alpha = (float)delta_time / 1000;

	if (alpha > 0.033)
	{
		alpha = 0.033;
	}
}

void MyFramework::move_bots(float alpha)
{
	for (int i=0; i<g_data.my_world.bots.size(); i++)
	{
		if (g_data.my_world.bots[i].alive == false)
		{
			continue;
		}

		b_logic.update_chunk(g_data.my_world.bots[i]);

		if (set.bot_number_for_game == i and set.spectator_mode == false)
		{
			b_logic.move_player(g_data.my_world.bots[i], alpha);
		}
		else
		{
			b_logic.bot_movement(g_data.my_world.bots[i], alpha);
		}
	}
}

void MyFramework::shooting(float alpha)
{
	for (int i = 0; i < g_data.my_world.bots.size(); i++)
	{
		if (g_data.my_world.bots[i].alive == true)
		{
			b_logic.update_visible_area(g_data.my_world.bots[i]);

			if (set.bot_number_for_game == i and set.spectator_mode == false)
			{
				b_logic.shooting_player(g_data.my_world.bots[i], getTickCount());
			}
			else
			{
				b_logic.shooting_bot(g_data.my_world.bots[i], getTickCount());
			}

			b_logic.move_bullets(g_data.my_world.bots[i], alpha);

			b_logic.check_bullets(g_data.my_world.bots[i]);

			b_logic.update_direction_viewing(g_data.my_world.bots[i]);
		}
		
	}
}

void MyFramework::restart_game()
{
	g_data.update_thermal_matrix_1();
	g_data.update_thermal_matrix_2();
	g_data.my_world.spawn_bots();
}

bool MyFramework::check_end_game()
{
	int n = 0;
	for (auto& i : g_data.my_world.bots)
	{
		if (i.alive == true)
		{
			n++;
		}
	}

	if (n > 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
