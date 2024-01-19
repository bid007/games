#include <iostream>
#include "include/raylib.h"
#include "box2d/box2d.h"

namespace Window
{
  const int WIDTH = 600;
  const int HEIGHT = 400;
  const int SIZE = 9;
  const char *TITLE = "ARKANOID";
}

class GameApp
{
private:
  const int x_pos = 2;
  const int y_pos = 2;
  const int WIDTH = 596;
  const int HEIGHT = 396;
  const Color bc = LIGHTGRAY;
  Rectangle bat;

public:
  GameApp()
  {
    bat = Rectangle{240, 375, 120, 20};
  }

  void move_bat_right()
  {
    if (bat.x + bat.width < Window::WIDTH)
      bat.x += 16.0f;
  }

  void move_bat_left()
  {
    if (bat.x > 0)
      bat.x -= 16.0f;
  }

  inline void update_bat()
  {
    if (IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT))
      move_bat_right();
    if (IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressed(KEY_LEFT))
      move_bat_left();
  }

  inline void draw()
  {
    DrawRectangle(x_pos, y_pos, WIDTH, HEIGHT, bc);
    DrawRectangleGradientV(bat.x, bat.y, bat.width, bat.height, MAGENTA, GOLD);
  }
};

class GameWorld
{
  std::vector<b2Body *> game_bodies;
  b2World *world;

public:
  GameWorld(b2World *w)
  {
    world = w;
    create_game_box();
  }

  void create_game_box()
  {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(300.0f, 380.0f);
    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(300.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    game_bodies.push_back(groundBody);
  }

  ~GameWorld()
  {
    for (auto &body : game_bodies)
    {
      world->DestroyBody(body);
    }
  }

  void draw()
  {
    DrawRectangle(0, 380, 600, 20, WHITE);
  }
};

int main()
{
  InitWindow(Window::WIDTH, Window::HEIGHT, Window::TITLE);
  SetTargetFPS(60);

  // Setup Box2d and game app
  // -----------------------------------------
  b2Vec2 gravity(0.0f, 50.0f);
  b2World world(gravity);

  // auto app = GameApp();
  auto app = GameWorld(&world);

  // b2BodyDef groundBodyDef;
  // groundBodyDef.position.Set(300.0f, 380.0f);
  // b2Body *groundBody = world.CreateBody(&groundBodyDef);
  // {
  //   b2PolygonShape groundBox;
  //   groundBox.SetAsBox(300.0f, 10.0f);
  //   groundBody->CreateFixture(&groundBox, 0.0f);
  // }
  // DrawRectangle(0, 380, 600, 20, WHITE);
  // DrawCircle(position.x, position.y, 10, WHITE);

  // b2BodyDef bodyDef;
  // bodyDef.type = b2_dynamicBody;
  // bodyDef.position.Set(50.0f, 40.0f);
  // b2Body *body = world.CreateBody(&bodyDef);
  // {
  //   b2PolygonShape dynamicBox;
  //   dynamicBox.SetAsBox(1.0f, 1.0f);
  //   b2FixtureDef fixtureDef;
  //   fixtureDef.shape = &dynamicBox;
  //   fixtureDef.density = 50.0f;
  //   fixtureDef.friction = 0.3f;
  //   fixtureDef.restitution = 0.9f;
  //   body->CreateFixture(&fixtureDef);
  // }
  // b2Vec2 position = body->GetPosition();

  constexpr float timeStep = 1.0f / 60.0f;
  constexpr int32 velocityIterations = 6;
  constexpr int32 positionIterations = 2;

  // -----------------------------------------

  while (!WindowShouldClose())
  {
    // Update the world and its objects
    // -----------------------------------------
    // app.update_bat();
    world.Step(timeStep, velocityIterations, positionIterations);
    // -----------------------------------------

    // Draw
    // -----------------------------------------
    BeginDrawing();
    ClearBackground(MAROON);
    app.draw();
    EndDrawing();
    // -----------------------------------------
  }
}
