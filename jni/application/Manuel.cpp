#include "Manuel.h"


Manuel::Manuel(Point2f &position_)
	   : Game_Object(position_, Vector2f(50.0f, 50.0f), 0.0f),
	   _faceRight(true), currentAnimation("manuel_default"), _maxHealth(100.0f),
	   _currentHealth(100.0f), _hasFire(true), _hasGrenade(false), _currentFrame(0),
	   _lastUpdate(0.0f), _flameOn(false), _lastHit(0.0f), _hit(false), _alter(true)
{
}

void Manuel::render() const
{
	if (_flameOn)
		_fireAnimation.render();
	if (!_hit || _alter)
		Game_Object::render(currentAnimation);
}

void Manuel::animate(const float timeStep)
{
	if (_flameOn)
	{
		float offset = get_size().x;
		if (! _faceRight)
			offset *= -1.0f;
		_fireAnimation.animate(timeStep, get_position() + Vector2f(offset, 0.0f), _faceRight);

	}
	if (timeStep - _lastHit > 0.1f)
	{
		_hit = false;
	}
	if (_hit)
		_alter = !_alter;
}

Bullet * Manuel::fire()
{
	return new Bullet(get_center(), Vector2f(8.0f, 8.0f), 0, _faceRight);
}

void Manuel::move(const float &move_x, const float &move_y, const list<Seat *>& seats)
{

	float moveX = move_x;
	float moveY = move_y;

	if (move_x < 0 && _faceRight)
	{
		_faceRight = false;
		currentAnimation += "_left";
	}
	else if (move_x > 0 && !_faceRight)
	{
		_faceRight = true;
		currentAnimation.erase(currentAnimation.find("_left"), currentAnimation.size());
	}

	const Vector2f man_size = get_size();
	const Point2f posX = get_position() + Vector2f(move_x, 0.0f);
	const Point2f posY = get_position() + Vector2f(0.0f, move_y);


	for (list<Seat *>::const_iterator it = seats.begin(); it != seats.end(); ++it)
	{
		const Vector2f seat_size = (*it)->get_size();

		Vector2f dist_vec = posX - (*it)->get_position() +
		0.5f * (man_size - seat_size);

		float distX = (dist_vec.x < 0) ? (-1.0f) * dist_vec.x : dist_vec.x;
		float distY = (dist_vec.y < 0) ? (-1.0f) * dist_vec.y : dist_vec.y;

		if ((0.5f) * (seat_size.x + man_size.x) - 5.0f > distX && (0.5f) * (seat_size.y + man_size.y) - 5.0f > distY)
			moveX = 0.0f;

		dist_vec = posY - (*it)->get_position() +
		0.5f * (man_size - seat_size);

		distX = (dist_vec.x < 0) ? (-1.0f) * dist_vec.x : dist_vec.x;
		distY = (dist_vec.y < 0) ? (-1.0f) * dist_vec.y : dist_vec.y;

		if ((0.5f) * (seat_size.x + man_size.x) - 5.0f > distX && (0.5f) * (seat_size.y + man_size.y) - 5.0f > distY)
			moveY = 0.0f;
	}

	if (posY.y < 34.0f || posY.y > 280.0f)
		moveY = 0.0f;

	if (posX.x < 0.0f || posX.x > 590.0f)
		moveX = 0.0;

	Game_Object::move(moveX, moveY);
}

void Manuel::changeHealth(const float &amount_)
{
	_currentHealth += amount_;
	if (_currentHealth < 0)
		_currentHealth = 0.0f;
	if (_currentHealth > _maxHealth)
		_currentHealth = _maxHealth;
}

const float Manuel::getHealth() const
{
	return _currentHealth;
}

const float Manuel::getMaxHealth() const
{
	return _maxHealth;
}

const bool Manuel::hasFire() const
{
	return _hasFire;
}

const bool Manuel::hasGrenade() const
{
	return _hasGrenade;
}

void Manuel::setFire(const bool fire_)
{
	_hasFire = fire_;
}

void Manuel::setGrenade(const bool grenade_)
{
	_hasGrenade = grenade_;
}

void Manuel::startFlame()
{
	_flameOn = true;
}

void Manuel::endFlame()
{
	_flameOn = false;
	_fireAnimation.reset();
}

const bool Manuel::flameOn() const
{
	return _flameOn;
}

const Fire * Manuel::getFlames() const
{
	return &_fireAnimation;
}

const bool Manuel::isAlive() const
{
	return (_currentHealth > 0.0f);
}

void Manuel::hasBeenHit(const float time)
{
	_lastHit = time;
	_hit = true;
}