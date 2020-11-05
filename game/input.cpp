#include "input.h"

input& input::instance()
{
	static input instance;
	return instance;
}