#pragma once

#include "Screen.h"

class ExitScreen: public Screen
{
public:
	ExitScreen(){};
	const bool IsExit(){ return true; };
};