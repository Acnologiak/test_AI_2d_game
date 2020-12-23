#pragma once

#include "Framework.h"
#include "settings.h"
#include "input.h"
#include "game_data.h"
#include "world_rendering.h"
#include "bot_logic.h"

#include <iostream>

class MyFramework : public Framework {

public:
	virtual void PreInit(int& width, int& height, bool& fullscreen);
	virtual bool Init();
	virtual void Close();
	virtual bool Tick();
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
	virtual void onKeyPressed(FRKey k);
	virtual void onKeyReleased(FRKey k);

private:
	settings& set = settings::instance();
	input& inp = input::instance();
	game_data& g_data = game_data::instance();
	world_rendering& w_rendering = world_rendering::instance();
	bot_logic& b_logic = bot_logic::instance();

	//��� ��������� ���������
	unsigned int last_time = 0;
	//��� �� �����������
	unsigned int delta_time = 0;
	//��� �� �������
	float alpha = 0;

	//��������� ���� �� �������
	void update_alpha();


	void move_bots(float);
	void shooting(float);
	void restart_game();
	bool check_end_game();
};