#include <iostream>
#include "include/raylib.h"
#include "box2d/box2d.h"
#include "constants.h"
#include "game_world.h"

int main()
{
  InitWindow(Window::WIDTH, Window::HEIGHT, Window::TITLE);
  SetTargetFPS(60);

  // Setup Box2d and game app
  // -----------------------------------------
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);

  constexpr float timeStep = 1.0f / 60.0f;
  constexpr int32 velocityIterations = 6;
  constexpr int32 positionIterations = 2;

  auto app = GameWorld(&world);
  bool start = false;
  // -----------------------------------------

  while (!WindowShouldClose())
  {
    // Update the world and its objects
    // -----------------------------------------
    if (!start)
    {
      app.apply_force_to_ball();
      start = true;
    }

    world.Step(timeStep, velocityIterations, positionIterations);
    // -----------------------------------------

    // Draw
    // -----------------------------------------
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    app.draw();
    EndDrawing();
    // -----------------------------------------
  }
}
