#include "Background.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

Background::Background(const Vector2f &size_)
	: Game_Object(Point2f (0.0f, 0.0f), size_, 0.0f)
{
	for (int i = 0; i < 4; ++i)
	{
		_clouds[i] = Cloud();
		_clouds[i].setPosition(Point2f(-107.0f + (213.0f * i), -5.0f));
	}
	for (int i = 0; i < 1; ++i)
	{
		_stormColors[i] = Color(0.5f, 0.0f, 0.0f, 112.0f);
	}
}

void Background::render()
	const
{
	for (int i = 0; i < 4; ++i)
	{
		_clouds[i].render();
	}
	Video &vr = get_Video();
	Vertex2f_Color q0(Point2f(0.0f, 0.0f), _stormColors[0]);
    Vertex2f_Color q1(Point2f(0.0f, 360.0f), _stormColors[0]);
    Vertex2f_Color q2(Point2f(640.0f, 360.0f), _stormColors[0]);
	Vertex2f_Color q3(Point2f(640.0f, 0.0f), _stormColors[0]);
	Quadrilateral<Vertex2f_Color> quad(q0, q1, q2, q3);
	vr.render(quad);

	Game_Object::render("background");
}

void Background::animate(const float time)
{
	for (int i = 0; i < 4; ++i)
	{
		_clouds[i].move(1.0f, 0.0f);
		if (_clouds[i].get_position().x > 640.0f)
		{
			_clouds[i].setPosition(Point2f(-107.0f, -5.0f));
		}
	}
}