#include "players.h"


players& players::instance()
{
	static players instance;
	return instance;
}

void players::spawn_bots()
{
	g_data.bots.clear();
	int p = 0;
	while (true)
	{
		if (p == 16)
		{
			break;
		}
		int x = rand() % set.world_size.x;
		int y = rand() % set.world_size.y;

		if (g_data.info_matrix[x][y] == '1')
		{
			creature c;
			c.spr.load_sprite("sprites/team1.png");
			c.position.x = (float)x * set.block_size.x + set.block_size.x / 2 - c.spr.center.x;
			c.position.y = (float)y * set.block_size.y + set.block_size.y / 2 - c.spr.center.y;
			c.id = p;
			p++;
			g_data.bots.emplace_back(c);
		}
	}
}
