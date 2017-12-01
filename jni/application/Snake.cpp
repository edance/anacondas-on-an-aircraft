#include "Snake.h"
#include <zenilib.h>
#include <sstream>


using namespace std;
using namespace Zeni;

Snake::Snake(const Point2f &position_, const float &velocity_, const bool facing_right)
	: Game_Object(position_, Vector2f(64.0f, 64.0f), 0.0f),
	_alive(true), _terminal(false), _lastUpdate(0.0f),
	_curFrame(0), _numFrames(2), _VELOCITY(velocity_),
	currentAnimation("snake0"), _facingRight(facing_right)
{
}

void Snake::render()
	const
{
	Game_Object::render(currentAnimation);
}

void Snake::animate(const float timeStep)
{
	if (_alive)
	{
		if (timeStep - _lastUpdate > 0.5f)
		{
			_curFrame = (_curFrame + 1) % _numFrames;
			ostringstream oss;
			oss << "snake" << _curFrame;
			if (!_facingRight)
				oss << "_left";
			currentAnimation = oss.str();
			_lastUpdate = timeStep;
		}
	}
	else if (_curFrame == 2)
	{
		if (timeStep - _lastUpdate > 5.0f)
			_terminal = true;
	}
	else
	{
		if (timeStep - _lastUpdate > 0.1f)
		{
			++ _curFrame;
			ostringstream oss;
			oss << "snake_shot" << _curFrame;
			if (!_facingRight)
				oss << "_left";
			currentAnimation = oss.str();
			_lastUpdate = timeStep;
		}
	}
}

bool Snake::isAlive()
{
	return _alive;
}

bool Snake::isTerminal()
{
	return _terminal;
}

void Snake::killSnake()
{
	_alive = false;
	if (!_facingRight)
		currentAnimation = "snake_shot0_left";
	else
		currentAnimation = "snake_shot0";
	_curFrame = 0;
}

void Snake::move(const Point2f attackPoint, const list<Seat *>& seats)
{
	if (_alive)
	{
		bool collide_x = false;
		bool collide_y = false;

		const Point2f position = get_position();
		const float distX = attackPoint.x - position.x;
		const float distY = attackPoint.y - position.y;
		int pos = currentAnimation.find("_left");
		if (distX < 0)
		{
			if (pos != -1)
				currentAnimation.erase(pos, currentAnimation.size());
			_facingRight = true;
		}
		else
		{
			if (pos == -1)
				currentAnimation += "_left";
			_facingRight = false;
		}
		//currentAnimation.erase(currentAnimation.find("_left"), currentAnimation.size());
		float magnitude = (float)sqrt((double)(distX * distX + distY * distY));
		//travel at 2.5
		float ratio = _VELOCITY / magnitude;

		float moveX = ratio * distX;
		float moveY = ratio * distY;

		const Vector2f man_size = get_size();
		const Point2f posX = get_position() + Vector2f(moveX, 0.0f);
		const Point2f posY = get_position() + Vector2f(0.0f, moveY);


		for (list<Seat *>::const_iterator it = seats.begin(); it != seats.end(); ++it)
		{
			const Vector2f seat_size = (*it)->get_size();

			Vector2f dist_vec = posX - (*it)->get_position() + 
			0.5f * (man_size - seat_size);
	
			float distX = (dist_vec.x < 0) ? (-1.0f) * dist_vec.x : dist_vec.x;
			float distY = (dist_vec.y < 0) ? (-1.0f) * dist_vec.y : dist_vec.y;

			if ((0.5f) * (seat_size.x + man_size.x) - 5.0f > distX && (0.5f) * (seat_size.y + man_size.y) - 5.0f > distY)
			{
				moveX = 0.0f;
				if ((*it)->isOnFire())
				{
					moveY = 0.0f;
					killSnake();
					break;
				}
			}
		
			dist_vec = posY - (*it)->get_position() + 
			0.5f * (man_size - seat_size);
	
			distX = (dist_vec.x < 0) ? (-1.0f) * dist_vec.x : dist_vec.x;
			distY = (dist_vec.y < 0) ? (-1.0f) * dist_vec.y : dist_vec.y;

			if ((0.5f) * (seat_size.x + man_size.x) - 5.0f > distX && (0.5f) * (seat_size.y + man_size.y) - 5.0f > distY)
			{
				moveY = 0.0f;
				if ((*it)->isOnFire())
				{
					moveX = 0.0f;
					killSnake();
					break;
				}

			}
		}
		Game_Object::move(moveX, moveY);
	}
}