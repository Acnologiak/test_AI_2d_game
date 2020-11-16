#pragma once

#include <iostream>
#include "Framework.h"
#include "players.h"
#include "world.h"

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
	input& inp = input::instance();
	settings& set = settings::instance();
	players& plrs = players::instance();
	world& my_world = world::instance();

	float alpha{ 0.0 };
	unsigned int delta_time{ 0 };
	unsigned int last_time{ 0 };

	void update_alpha();
};