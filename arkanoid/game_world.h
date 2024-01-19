
#include <vector>
#include "include/raylib.h"
#include "box2d/box2d.h"

class GameWorld
{
  // Game world decorations
  const int x_pos = 2;
  const int y_pos = 2;
  const int WIDTH = 596;
  const int HEIGHT = 396;
  const Color bc = LIGHTGRAY;

  // Physics body containers
  std::vector<b2Body *> game_bodies;
  b2World *world;

public:
  GameWorld(b2World *w);
  void create_game_box();
  void create_ball();
  void draw();
  ~GameWorld();
};
