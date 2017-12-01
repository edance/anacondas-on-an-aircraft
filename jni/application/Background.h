#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include "Cloud.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Background : public Game_Object
{
public:
	Background(const Vector2f &size_);
	void render() const;
	void animate(const float time);

private:
	Cloud _clouds[4];
	Color _stormColors[1];
};

