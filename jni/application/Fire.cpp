#include "Fire.h"

using namespace std;

Fire::Fire()
  : Game_Object(Point2f(-50.0f, -50.0f), Vector2f(50.0f, 50.0f), 0.0f),
  _currentAnimation("flame0"),
  _currentFrame(0), _lastUpdate(0.0f)
{
}

void Fire::animate(const float timeStep, const Point2f &position, const bool faceRight)
{
  Game_Object::setPosition(position);
  if (_currentFrame == 4)
    _currentFrame -= 2;
  if (timeStep - _lastUpdate > 0.3)
  {
    ostringstream oss;
    oss << "flame" << _currentFrame ++;
    if (!faceRight)
      oss << "_left";
    _currentAnimation = oss.str();
  }
}

void Fire::reset()
{
  setPosition(Point2f(-50.0f, -50.0f));
  _currentFrame = 0;
  _currentAnimation = "flame0";
}


void Fire::render()
  const
{
  Game_Object::render(_currentAnimation);
}
