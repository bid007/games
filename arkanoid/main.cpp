#include <iostream>
#include "include/raylib.h"
#include "box2d/box2d.h"
#include "constants.h"
#include "game_world.h"
#include "contact_listener.h"

int main()
{
  InitWindow(Window::WIDTH, Window::HEIGHT, Window::TITLE);
  SetTargetFPS(60);

  // Setup Box2d and game app
  // -----------------------------------------
  b2Vec2 gravity(0.0f, 0.0f);
  ArkanoidContactListner *c_listener = new ArkanoidContactListner();
  b2World world(gravity);
  world.SetContactListener(c_listener);
  // world.SetDestructionListener();

  constexpr float timeStep = 1.0f / 60.0f;
  constexpr int32 velocityIterations = 6;
  constexpr int32 positionIterations = 2;

  auto app = GameWorld(&world);
  bool start = false;
  // -----------------------------------------

  while (!WindowShouldClose() && !c_listener->game_end())
  {
    // Update the world and its objects
    // -----------------------------------------
    if (!start)
    {
      app.apply_force_to_ball();
      start = true;
    }
    app.move_bat();
    world.Step(timeStep, velocityIterations, positionIterations);
    // -----------------------------------------

    // Draw
    // -----------------------------------------
    BeginDrawing();
    ClearBackground(GRAY);
    app.draw();
    EndDrawing();
    // -----------------------------------------
  }

  // Cleanup
  // -----------------------------------------
  delete c_listener;
  // -----------------------------------------
}
