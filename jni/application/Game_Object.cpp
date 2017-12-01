#include "Game_Object.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

Game_Object::Game_Object(const Point2f &position_,
		const Vector2f &size_,
		const float &theta_,
		const float &speed_)
		: m_position(position_),
		m_size(size_),
		m_theta(theta_),
		m_speed(speed_)
{
}


Game_Object::~Game_Object(void)
{
}

void Game_Object::render(const String &texture, const Color &filter)
	const
{
	/*Video &vr = get_Video();
	Colors &cr = get_Colors();
	vr.apply_Texture(texture);
	Vertex2f_Texture q0(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f));
    Vertex2f_Texture q1(Point2f(0.0f, 300.0f), Point2f(0.0f, 1.0f));
    Vertex2f_Texture q2(Point2f(1000.0f, 300.0f), Point2f(1.0f, 1.0f));
	Vertex2f_Texture q3(Point2f(1000.0f, 0.0f), Point2f(1.0f, 0.0f));
	Quadrilateral<Vertex2f_Texture> quad(q0, q1, q2, q3);
	vr.render(quad);
	*/
	render_image(
		texture,
		m_position,
		m_position + m_size,
		m_theta,
		1.0f,
		m_position + 0.5f * m_size,
		false,
		filter);
}

void Game_Object::move(const float &move_x, const float &move_y)
{
	m_position.y += move_y;
	m_position.x += move_x;
}

const Point2f &Game_Object::get_position() const
{
	return m_position;
}

const Vector2f &Game_Object::get_size() const
{
	return m_size;
}

const float Game_Object::get_radius() const
{
	return 0.5f * m_size.magnitude();
}

const Point2f Game_Object::get_center() const
{
	return Point2f(m_position.x + (m_size.x / 2.0f), m_position.y + (m_size.y / 2.0f));
}


bool Game_Object::collide(const Game_Object *obj) const
{
	const Vector2f obj_size = obj->get_size();

	const Vector2f dist_vec = m_position - obj->get_position() + 
		0.5f * (m_size - obj_size);
	
	const float distX = (dist_vec.x < 0) ? (-1.0f) * dist_vec.x : dist_vec.x;
	const float distY = (dist_vec.y < 0) ? (-1.0f) * dist_vec.y : dist_vec.y;

	return ((0.5f) * (obj_size.x + m_size.x) > distX && (0.5f) * (obj_size.y + m_size.y) > distY);
}

void Game_Object::setPosition(const Point2f &position_)
{
	m_position = position_;
}