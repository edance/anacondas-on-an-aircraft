#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Bullet : public Game_Object
{

public:
	Bullet(const Point2f &position_,
         const Vector2f &size_,
         const float &theta_, const bool movingRight);

	void render() const;
	void move(const float &move_x, const float &move_y);

private:
	bool _rightMoving;

};

