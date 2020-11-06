#pragma once

#include <iostream>
#include "Framework.h"
#include "world.h"
#include "settings.h"
#include "input.h"

/* Test Framework realization */
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
	world& my_world = world::instance();
	settings& set = settings::instance();
	input& inp = input::instance();

	//час останього оновлення
	unsigned int last_time = 0;
	//час між оновленнями
	unsigned int delta_time = 0;
	//час між кадрами
	float alpha = 0;

	void update_alpha();

	void draw_players();
	void draw_world();
	void draw_fog();
};