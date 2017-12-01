#pragma once
#include <zenilib.h>
#include <sstream>
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif

using namespace std;
using namespace Zeni;

class Seat : public Game_Object
{
public:
	Seat(const Point2f &midpoint_);
	void render() const;
	const Point2f get_center() const;
	bool collideX(const Game_Object *obj) const;
	bool collideY(const Game_Object *obj) const;
	void animate(const float timeStep);
	void setOnFire(const float time);
	const bool isOnFire() const;

private:
	Point2f _center;
	String _currentAnimation;
	int _currentFrame;
	float _lastUpdate;
	bool _onFire;
	float _onFireTime;
};

