#include "Anacondas.h"

Anacondas::Anacondas(const float width, const float height, const float framesPerSec)
  :_manuel(Point2f (0.0f, 0.0f)),
  _keylistener(),
  _time_passed(0.0f),
  _FRAMES_SEC(framesPerSec),
  _healthBar(), _score(), _powerBar(), _snakesPerSecond(0.25f)
{
  _HEIGHT = height;
  _WIDTH = width;
  _background = new Background(Vector2f(1024.0f, 512.0f));
  _manuel.move(10.0f, _HEIGHT / 2 - 32.0f, _seats);
  _chrono.start();
  _seats.push_back(new Seat(Point2f(151.0f, 129.0f)));
  _seats.push_back(new Seat(Point2f(267.0f, 129.0f)));
  _seats.push_back(new Seat(Point2f(384.0f, 129.0f)));
  _seats.push_back(new Seat(Point2f(499.0f, 129.0f)));
  _seats.push_back(new Seat(Point2f(615.0f, 129.0f)));
  _seats.push_back(new Seat(Point2f(151.0f, 249.0f)));
  _seats.push_back(new Seat(Point2f(267.0f, 249.0f)));
  _seats.push_back(new Seat(Point2f(384.0f, 249.0f)));
  _seats.push_back(new Seat(Point2f(499.0f, 249.0f)));
  _seats.push_back(new Seat(Point2f(615.0f, 249.0f)));
}

bool Anacondas::on_key(const SDL_KeyboardEvent &event)
{
  return _keylistener.on_key(event);
}

void Anacondas::render()
{
  get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(_WIDTH, _HEIGHT)), true);
  //render background
  _background->render();

  for (list<Bullet *>::const_iterator it = _bullets.begin(); it != _bullets.end(); ++it)
    (*it)->render();

  for (list<Snake *>::const_iterator it = _snakes.begin(); it != _snakes.end(); ++it)
    (*it)->render();

  for (list<Game_Object *>::const_iterator it = _powerups.begin(); it != _powerups.end(); ++it)
    (*it)->render();

  for (list<Seat *>::const_iterator it = _seats.begin(); it != _seats.end(); ++it)
    (*it)->render();

  _score.render();

  _healthBar.render();

  _powerBar.render();

  //render Manuel
  _manuel.render();

  if (!_manuel.isAlive())
  {
    //Show game over screen
    Video &vr = get_Video();
    Color color(0.5f, 0.0f, 0.0f, 0.0f);

    Vertex2f_Color v0(Point2f(0.0f, 0.0f), color);
    Vertex2f_Color v1(Point2f(0.0f, _HEIGHT), color);
    Vertex2f_Color v2(Point2f(_WIDTH, _HEIGHT), color);
    Vertex2f_Color v3(Point2f(_WIDTH, 0.0f), color);
    Quadrilateral<Vertex2f_Color> quad(v0, v1, v2, v3);
    vr.render(quad);

    Font &fr = get_Fonts()["system_36_x600"];

    ostringstream oss;
    oss << "Game Over\nScore: " << _score.getScore() << "\nPress Enter to Continue";

    fr.render_text(
      (String)oss.str(),
      Point2f(_WIDTH / 2.0f, _HEIGHT / 2.0f - (0.5f * fr.get_text_height() * 3)),
                   get_Colors()["title_text"],
                   ZENI_CENTER);

  }

}

void Anacondas::think()
{
  _projector = Projector2D(make_pair(Point2f(0.0f, 0.0f), Point2f(_WIDTH, _HEIGHT)), get_Video().get_viewport());
  const float time_passed = _chrono.seconds();
  const float time_step = time_passed - _time_passed;
  if (_manuel.isAlive())
  {
    if (time_step >= 1.0f / _FRAMES_SEC)
    {
      _time_passed = time_passed;

      if (_keylistener.fire)
      {
        if (_manuel.hasFire())
        {
          if (_powerBar.getAmount() == 0.0f)
          {
            _manuel.endFlame();
            _manuel.setFire(false);
            _powerBar.changeAmount(100.0f);
          }
          else
          {
            _manuel.startFlame();
            _powerBar.changeAmount(-1.0f);
          }
        }
        else
        {
          _keylistener.fire = false;
          _bullets.push_back(_manuel.fire());
        }
      }
      else
      {
        if (_manuel.hasFire())
        {
          _manuel.endFlame();
        }
      }

      moveBullets();

      removeBullets();

      _manuel.move((_keylistener.getRight() - _keylistener.getLeft()) * time_step * 150.0f,
        (_keylistener.getDown() - _keylistener.getUp()) * time_step * 150.0f, _seats);


      /* Loop through the snakes */

      for (list<Snake *>::const_iterator it = _snakes.begin(); it != _snakes.end();)
      {
        (*it)->move(_manuel.get_center(), _seats);
        if ((*it)->isAlive())
        {
          /* Shoot the snakes */
          for (list<Bullet *>::const_iterator bul_it = _bullets.begin(); bul_it != _bullets.end();)
          {
            if ((*it)->collide(*bul_it))
            {
              (*it)->killSnake();
              delete (*bul_it);
              bul_it = _bullets.erase(bul_it);
              _score.changeScore(999);
              break;
            }
            else
              ++bul_it;
          }

          /* Manuel and snake collision */
          if ((*it)->collide(&_manuel))
          {
              // make manuel flash
              _manuel.hasBeenHit(time_passed);
              _manuel.changeHealth(-0.25f);
          }

          /* Flame thrower collision */
          if (_manuel.flameOn() && (*it)->collide(_manuel.getFlames()))
            (*it)->killSnake();

          ++it;
        }
        else if ((*it)->isTerminal())
        {
          delete (*it);
          it = _snakes.erase(it);
        }
        else
          ++it;
      }

      /* Light Seats on Fire */
      for (list<Seat *>::const_iterator it = _seats.begin(); it != _seats.end(); ++it)
        if (_manuel.flameOn() && (*it)->collide(_manuel.getFlames()))
          (*it)->setOnFire(time_passed);

      /* Pick up packages */

      for (list<Game_Object *>::const_iterator it = _powerups.begin(); it != _powerups.end();)
      {
        if ((*it)->collide(&_manuel))
        {
          if (dynamic_cast<HealthPowerup *>(*it))
            _manuel.changeHealth(25.0f);
          else if (dynamic_cast<FirePowerup *>(*it))
          {
            _powerBar.changeAmount(100.0f);
            _manuel.setFire(true);
          }
          delete (*it);
          it = _powerups.erase(it);
        }
        else
          ++it;
      }

      /* Spawn Powerups */
      spawnPowerups();

      /* Spawn Snakes */
      spawnSnake();


      /* Update Health */
      _healthBar.setHealth(_manuel.getHealth());

      /* Update Score */
      _score.changeScore(1);

      /* Increase Difficulty */
      _snakesPerSecond += 0.0025f;
      if (_snakesPerSecond > 40.0f)
        _snakesPerSecond = 40.0f;


      /* Animation of the snakes */

      animate(time_passed);


    }
  }
  else
  {
    if (_keylistener.getEnter())
    {
      get_Game().pop_state();
    }
  }
}

void Anacondas::spawnSnake()
{
  if (rand() % ((int)(40.0f / _snakesPerSecond)) == 1)
  {
    //come from 8 different spots
    int spot = rand() % 8;

    float PosY = (spot < 4) ? 34.0f : 280.0f;

    float PosX = 209.0f + ((spot % 4) * 116.5f);

    _snakes.push_back(new Snake(Point2f(PosX, PosY)));
  }
}

void Anacondas::moveBullets()
{
  for (list<Bullet *>::const_iterator it = _bullets.begin(); it != _bullets.end(); ++it)
  {
    (*it)->move(25.0f, 0.0f);
  }
}

void Anacondas::removeBullets()
{
  for (list<Bullet *>::const_iterator it = _bullets.begin(); it != _bullets.end();)
  {
    const Point2f &p = (*it)->get_position();
    if (p.x < -10.0f || p.x > 10.0f + _WIDTH)
    {
      delete *it;
      it = _bullets.erase(it);
    }
    else
      ++it;
  }
}

void Anacondas::animate(const float timeStep)
{
  _background->animate(timeStep);

  for (list<Snake *>::const_iterator it = _snakes.begin(); it != _snakes.end(); ++it)
    (*it)->animate(timeStep);

  for (list<Seat *>::const_iterator it = _seats.begin(); it != _seats.end(); ++it)
    (*it)->animate(timeStep);

  _manuel.animate(timeStep);
}

void Anacondas::spawnPowerups()
{
  // there are three powerups
  // randomize between the two
  if (rand() % (40 * 10) == 1)
  {

    int randPosX = (rand() % (int)(_WIDTH - 100.f)) + 50;

    int randPosY = (rand() % (int)(_HEIGHT - 100.0f)) + 50;

    int selectPowerup = rand() % 4;

    Game_Object * powerup;

    switch (selectPowerup)
    {
      case 0:
        powerup = new HealthPowerup(Point2f((float)randPosX, (float)randPosY));
        break;
      default:
        powerup = new FirePowerup(Point2f((float)randPosX, (float)randPosY));
        break;
    }

    _powerups.push_back(powerup);
  }
}

const list<Seat *>* Anacondas::getSeats() const
{
  return &_seats;
}
