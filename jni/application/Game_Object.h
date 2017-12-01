#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Game_Object
{
public:
	Game_Object(const Point2f &position_,
		const Vector2f &size_,
		const float &theta_ = 0.0f,
		const float &speed_ = 0.0f);
	virtual ~Game_Object();
	virtual void render() const = 0;
	void move(const float &move_x, const float &move_y);
	const Point2f &get_position() const;
	const Vector2f &get_size() const;
	const Point2f get_center() const;
	const float get_radius() const;
	bool collide(const Game_Object *obj) const;
	void setPosition(const Point2f &position_);

private:
	Point2f m_position;
	Vector2f m_size;
	float m_theta;
	float m_speed;

protected:
	void render(const String &texture, const Color &filter = Color()) const;
};

