#pragma once
#ifndef GAME_OBJECT
#include "Game_Object.h"
#include "Bullet.h"
#include "Seat.h"
#include <sstream>
#include "Fire.h"
#endif

class Manuel : public Game_Object
{
public:
	Manuel(Point2f &position_);
	void render() const;
	void animate(const float timeStep);
	Bullet * fire();
	void move(const float &move_x, const float &move_y, const list<Seat *>& seats);
	void changeHealth(const float &amount_);
	const float getHealth() const;
	const float getMaxHealth() const;
	const bool hasFire() const;
	const bool hasGrenade() const;
	void setFire(const bool fire_);
	void setGrenade(const bool grenade_);
	void startFlame();
	void endFlame();
	const bool flameOn() const;
	const Fire * getFlames() const;
	const bool isAlive() const;
	void hasBeenHit(const float time);


private:
	bool _hasFire;
	bool _hasGrenade;
	bool _faceRight;
	bool _flameOn;
	bool _hit;
	bool _alter;
	int _currentFrame;
	String currentAnimation;
	const float _maxHealth;
	float _currentHealth;
	float _lastUpdate;
	float _lastHit;
	Fire _fireAnimation;
};

