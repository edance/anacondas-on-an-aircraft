#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class HealthPowerup : public Game_Object
{
public:
	HealthPowerup(const Point2f &position_);
	void render() const;
};

