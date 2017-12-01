#include "HealthBar.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

HealthBar::HealthBar()
	: _maxHealth(100.0f),
	_currentHealth(100.0f)
{
}

void HealthBar::render()
	const
{
	Video &vr = get_Video();
	vr.apply_Texture((String)"heart");
	Vertex2f_Texture v0(Point2f(5.0f, 315.0f), Point2f(0.0f, 0.0f));
	Vertex2f_Texture v1(Point2f(5.0f, 335.0f), Point2f(0.0f, 1.0f));
	Vertex2f_Texture v2(Point2f(25.0f, 335.0f), Point2f(1.0f, 1.0f));
	Vertex2f_Texture v3(Point2f(25.0f, 315.0f), Point2f(1.0f, 0.0f));
	Quadrilateral<Vertex2f_Texture> hquad(v0, v1, v2, v3);
	vr.render(hquad);
	vr.unapply_Texture();

	vr.apply_Texture((String)"gun");
	Vertex2f_Texture g0(Point2f(485.0f, 315.0f), Point2f(0.0f, 0.0f));
	Vertex2f_Texture g1(Point2f(485.0f, 335.0f), Point2f(0.0f, 1.0f));
	Vertex2f_Texture g2(Point2f(505.f, 335.0f), Point2f(1.0f, 1.0f));
	Vertex2f_Texture g3(Point2f(505.f, 315.0f), Point2f(1.0f, 0.0f));
	Quadrilateral<Vertex2f_Texture> gquad(g0, g1, g2, g3);
	vr.render(gquad);
	vr.unapply_Texture();

	Colors &cr = get_Colors();
	Vertex2f_Color q0(Point2f(30.0f, 320.0f), cr["red"]);
    Vertex2f_Color q1(Point2f(30.0f, 330.0f), cr["red"]);
    Vertex2f_Color q2(Point2f(130.0f, 330.0f), cr["green"]);
	Vertex2f_Color q3(Point2f(130.0f, 320.0f), cr["green"]);
	Quadrilateral<Vertex2f_Color> quad(q0, q1, q2, q3);
	vr.render(quad);

	float ratio = _currentHealth / _maxHealth;
	ratio *= 100.0f;
	ratio += 30.0f;

	Vertex2f_Color b0(Point2f(ratio, 320.0f), cr["black"]);
    Vertex2f_Color b1(Point2f(ratio, 330.0f), cr["black"]);
    Vertex2f_Color b2(Point2f(130.0f, 330.0f), cr["black"]);
	Vertex2f_Color b3(Point2f(130.0f, 320.0f), cr["black"]);
	Quadrilateral<Vertex2f_Color> bquad(b0, b1, b2, b3);
	vr.render(bquad);
}


void HealthBar::setHealth(const float amount_)
{
	_currentHealth = amount_;
}

void HealthBar::setMaxHealth(const float amount_)
{
	_maxHealth = amount_;
}