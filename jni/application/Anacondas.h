#pragma once
#include <zenilib.h>
#include "Manuel.h"
#include "KeyListener.h"
#include "Background.h"
#include "Snake.h"
#include "HealthPowerup.h"
#include "FirePowerup.h"
#include "HealthBar.h"
#include "PowerBar.h"
#include "Score.h"
#include "Seat.h"
#include <sstream>

using namespace Zeni;

class Anacondas
{
public:
	Anacondas(const float width, const float height, const float framesPerSec);
	bool on_key(const SDL_KeyboardEvent &event);
	void render();
	void think();
	const list<Seat *>* getSeats() const;

private:
	float _HEIGHT;
	float _WIDTH;
	Background * _background;
	Manuel _manuel;
	KeyListener _keylistener;
	Chronometer<Time> _chrono;
	float _time_passed;
	Projector2D _projector;
	const float _FRAMES_SEC;
	list <Snake *>_snakes;
	list <Bullet *> _bullets;
	list <Game_Object *> _powerups;
	list <Seat *> _seats;
	HealthBar _healthBar;
	PowerBar _powerBar;
	Score _score;
	float _snakesPerSecond;

	void spawnSnake();
	void spawnPowerups();
	void moveBullets();
	void removeBullets();
	void animate(const float timeStep);
};

