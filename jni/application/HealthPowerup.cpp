#include "HealthPowerup.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

HealthPowerup::HealthPowerup(const Point2f &position_)
	: Game_Object(position_, Vector2f(25.0f, 25.0f), 0.0f)
{
}

void HealthPowerup::render()
	const
{
	Game_Object::render("health_powerup");
}