#include "FirePowerup.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

FirePowerup::FirePowerup(const Point2f &position_)
	: Game_Object(position_, Vector2f(25.0f, 25.0f), 0.0f)
{
}

void FirePowerup::render()
	const
{
	Game_Object::render("fire_powerup");
}