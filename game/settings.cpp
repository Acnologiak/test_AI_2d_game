#include "settings.h"


settings& settings::instance()
{
	static settings instance;
	return instance;
}