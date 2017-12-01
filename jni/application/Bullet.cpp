#include "Bullet.h"

using namespace std;

Bullet::Bullet(const Point2f &position_,
         const Vector2f &size_,
         const float &theta_, const bool movingRight)
  : Game_Object(position_, size_, theta_),
  _rightMoving(movingRight)
{
}


void Bullet::render()
  const
{
  Game_Object::render("bullet");
}

void Bullet::move(const float &move_x, const float &move_y)
{
  const float factor = (_rightMoving) ? 1.0f : -1.0f;
  Game_Object::move(factor * move_x, move_y);
}
