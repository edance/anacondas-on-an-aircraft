#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#include <sstream>
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Fire : public Game_Object
{

public:
	Fire();

	void render() const;
	void animate(const float timeStep, const Point2f &position, const bool faceRight);
	void reset();

private:
	String _currentAnimation;
	int _currentFrame;
	float _lastUpdate;
};

