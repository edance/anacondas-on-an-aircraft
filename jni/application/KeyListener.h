#pragma once
#include <zenilib.h>

using namespace Zeni;

class KeyListener
{
public:
	KeyListener(void);
	bool on_key(const SDL_KeyboardEvent &event);

	/* Get Key Down Booleans */
	bool getUp();
	bool getDown();
	bool getRight();
	bool getLeft();
	bool getEnter();

	bool fire;

private:
	bool _up;
	bool _down;
	bool _right;
	bool _left;
	bool _enter;
};

