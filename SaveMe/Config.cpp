#include "Config.h"

float DISPLAY_RESX = 800.0f;
float DISPLAY_RESY = 600.0f;

void SetDisplayResolution(const float x, const float y)
{
	DISPLAY_RESX = x;
	DISPLAY_RESY = y;
}