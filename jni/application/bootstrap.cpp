/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>
#include "Anacondas.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

static const float SCREEN_WIDTH = 640.0f;
static const float SCREEN_HEIGHT = 360.0f;
static const float FRAMES_PER_SECOND = 24.0f;


class Play_State : public Gamestate_Base {
  Play_State(const Play_State &);
  Play_State operator=(const Play_State &);

public:
  Play_State()
  : _anacondas(SCREEN_WIDTH, SCREEN_HEIGHT, FRAMES_PER_SECOND)
  {
    set_pausable(true);
  }

private:
  void on_push() {
    //get_Window().mouse_grab(true);
    get_Window().mouse_hide(true);
    //get_Game().joy_mouse.enabled = false;
  }

  void on_pop() {
    //get_Window().mouse_grab(false);
    get_Window().mouse_hide(false);
    //get_Game().joy_mouse.enabled = true;
  }

  void on_key(const SDL_KeyboardEvent &event)
  {
	  if(!_anacondas.on_key(event)) Gamestate_Base::on_key(event);
  }

  void render()
  {
	  _anacondas.render();
  }

  void perform_logic()
  {
	  _anacondas.think();
  }

  Anacondas _anacondas;
};

class Instructions_State : public Widget_Gamestate {
  Instructions_State(const Instructions_State &);
  Instructions_State operator=(const Instructions_State &);

public:
  Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(SCREEN_WIDTH, SCREEN_HEIGHT)))
  {
  }

private:
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
  }

  void render() {
    Widget_Gamestate::render();

	Point2f position(0.0f, 0.0f);
	Vector2f size(SCREEN_WIDTH, SCREEN_HEIGHT);

	render_image(
		(String)"instructions",
		position,
		position + size,
		0.0f,
		1.0f,
		position + 0.5f * size,
		false,
		Color());
  }
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("Anacondas On An Aircraft");

      get_Joysticks();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();
      get_Game().joy_mouse.enabled = true;

      return new Title_State<Play_State, Instructions_State>("Anacondas On An Aircraft");
    }
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
