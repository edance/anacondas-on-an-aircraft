#include "Cloud.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

Cloud::Cloud()
	: Game_Object(Point2f (0.0f, 0.0f), Vector2f(64.0f, 64.0f), 0.0f)
{
}

void Cloud::render()
	const
{
	Game_Object::render("cloud");
}