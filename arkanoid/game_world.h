
#include <vector>
#include <iostream>
#include "include/raylib.h"
#include "box2d/box2d.h"

class GameWorld
{
  // Physics body containers
  std::vector<b2Body *> game_bodies;
  b2Body *walls[4];
  b2Body *ball;
  b2World *world;

public:
  GameWorld(b2World *w);
  void create_game_box();
  void create_ball();
  void apply_force_to_ball();
  void draw();
};
