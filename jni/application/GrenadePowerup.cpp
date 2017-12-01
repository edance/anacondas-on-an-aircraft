#include "GrenadePowerup.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

GrenadePowerup::GrenadePowerup(const Point2f &position_)
	: Game_Object(position_, Vector2f(25.0f, 25.0f), 0.0f)
{
}

void GrenadePowerup::render()
	const
{
	Game_Object::render("grenade_powerup");
}