#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class FirePowerup : public Game_Object
{
public:
	FirePowerup(const Point2f &position_);
	void render() const;
};

