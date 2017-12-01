#include "Seat.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

Seat::Seat(const Point2f &midpoint)
		: Game_Object(midpoint - Vector2f(21.5f, 21.0f), Vector2f(43.0f, 21.0f), 0.0f),
		_currentAnimation("seat_flame0"), _currentFrame(0), _lastUpdate(0.0f),
		_onFire(false), _onFireTime(0.0f)
{
}

void Seat::animate(const float timeStep)
{
	if (timeStep - _lastUpdate > 0.25)
	{
			_currentFrame = (_currentFrame + 1) % 2;
			ostringstream oss;
			oss << "seat_flame" << _currentFrame;
			_currentAnimation = oss.str();
			_lastUpdate = timeStep;
	}
	if (_onFire && timeStep - _onFireTime > 5.0f)
	{
		_onFire = false;
	}
}

void Seat::render()
	const
{
	// do nothing lol
	// if on fire
	if (_onFire)
	{
		Point2f position = get_position();
		Video &vr = get_Video();
		Colors &cr = get_Colors();
		vr.apply_Texture(_currentAnimation);
		Vertex2f_Texture q0(position, Point2f(0.0f, 0.0f));
		Vertex2f_Texture q1(position + Vector2f(0.0f, 36.0f), Point2f(0.0f, 1.0f));
		Vertex2f_Texture q2(position + Vector2f(36.0f, 36.0f), Point2f(1.0f, 1.0f));
		Vertex2f_Texture q3(position + Vector2f(36.0f, 0.0f), Point2f(1.0f, 0.0f));
		Quadrilateral<Vertex2f_Texture> quad(q0, q1, q2, q3);
		vr.render(quad);
		vr.unapply_Texture();
	}
}

const Point2f Seat::get_center() const
{
	return _center;
}


bool Seat::collideX(const Game_Object *obj) const
{
	const Vector2f size = get_size();
	const Vector2f obj_size = obj->get_size();

	float dist_X = get_position().x - obj->get_position().x +
		0.5f * (get_size().x - obj->get_size().x);

	dist_X = (dist_X < 0) ? (-1.0f) * dist_X : dist_X;

	if (dist_X < (0.5f) * (size.x + obj_size.x))
		return true;

	return false;
}

bool Seat::collideY(const Game_Object *obj) const
{
	const Vector2f size = get_size();
	const Vector2f obj_size = obj->get_size();

	float dist_Y = get_position().y - obj->get_position().y +
		0.5f * (get_size().y - obj->get_size().y);

	dist_Y = (dist_Y < 0) ? (-1.0f) * dist_Y : dist_Y;

	if (dist_Y < (0.5f) * (size.y + obj_size.y))
		return true;

	return false;
}

void Seat::setOnFire(const float time)
{
	_onFireTime = time;
	_onFire = true;
}

const bool Seat::isOnFire() const
{
	return _onFire;
}