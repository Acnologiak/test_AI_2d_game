#include "players.h"


players& players::instance()
{
	static players instance;
	return instance;
}