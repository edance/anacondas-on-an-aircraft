#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#endif
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Cloud : public Game_Object
{
public:
	Cloud();
	void render() const;
};

