#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class GrenadePowerup : public Game_Object
{
public:
	GrenadePowerup(const Point2f &position_);
	void render() const;
};

