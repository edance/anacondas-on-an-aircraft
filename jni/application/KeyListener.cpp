#include "KeyListener.h"

KeyListener::KeyListener()
	: _up(false), _down(false), _right(false), _left(false), fire(false), _enter(false)
{
}

bool KeyListener::on_key(const SDL_KeyboardEvent &event)
{
	switch(event.keysym.sym) {
      case SDLK_w:
		  _up = event.type == SDL_KEYDOWN;
		  break;
 
      case SDLK_a:
		  _left = event.type == SDL_KEYDOWN;
		  break;
 
      case SDLK_s:
		  _down = event.type == SDL_KEYDOWN;
		  break;
 
      case SDLK_d:
		  _right = event.type == SDL_KEYDOWN;
		  break;

	  case SDLK_SPACE:
		  fire = event.type == SDL_KEYDOWN;
		  break;

	  case SDLK_RETURN:
		  _enter = event.type == SDL_KEYDOWN;
		  break;

	  default:
		return false;
	}

	return true;
}

bool KeyListener::getUp()
{
	return _up;
}
bool KeyListener::getDown()
{
	return _down;
}
bool KeyListener::getRight()
{
	return _right;
}
bool KeyListener::getLeft()
{
	return _left;
}
bool KeyListener::getEnter()
{
	return _enter;
}