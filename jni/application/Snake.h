#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#include "Seat.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Snake : public Game_Object
{
public:
	Snake(const Point2f &position_, const float &velocity_ = 2.5f, const bool facing_right = true);
	void animate(const float timeStep);
	bool isAlive();
	bool isTerminal();
	void killSnake();
	void move(const Point2f attack, const list<Seat *>& seats);
	void render() const;

private:
	bool _alive;
	bool _terminal;
	bool _facingRight;
	String currentAnimation;
	float _lastUpdate;
	int _numFrames;
	int _curFrame;
	const float _VELOCITY;
};

