#include "PowerBar.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

PowerBar::PowerBar()
	: _maxAmount(100.0f),
	_currentAmount(50.0f)
{
}

void PowerBar::render()
	const
{
	Video &vr = get_Video();


	Colors &cr = get_Colors();
	Vertex2f_Color q0(Point2f(510.f, 320.0f), cr["yellow"]);
    Vertex2f_Color q1(Point2f(510.f, 330.0f), cr["yellow"]);
    Vertex2f_Color q2(Point2f(610.0f, 330.0f), cr["yellow"]);
	Vertex2f_Color q3(Point2f(610.0f, 320.0f), cr["yellow"]);
	Quadrilateral<Vertex2f_Color> quad(q0, q1, q2, q3);
	vr.render(quad);

	float ratio = _currentAmount / _maxAmount;
	ratio *= 100.0f;
	ratio += 510.0f;

	Vertex2f_Color b0(Point2f(ratio, 320.0f), cr["black"]);
    Vertex2f_Color b1(Point2f(ratio, 330.0f), cr["black"]);
    Vertex2f_Color b2(Point2f(610.0f, 330.0f), cr["black"]);
	Vertex2f_Color b3(Point2f(610.0f, 320.0f), cr["black"]);
	Quadrilateral<Vertex2f_Color> bquad(b0, b1, b2, b3);
	vr.render(bquad);
}


const float PowerBar::getAmount()
	const
{
	return _currentAmount;
}
void  PowerBar::changeAmount(const float amount_)
{
	_currentAmount += amount_;
	if (_currentAmount > _maxAmount) _currentAmount = _maxAmount;
	if (_currentAmount < 0) _currentAmount = 0;
}