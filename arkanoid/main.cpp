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
  void draw()
  {
    DrawRectangle(x_pos, y_pos, WIDTH, HEIGHT, bc);
    DrawRectangleGradientV(bat.x, bat.y, bat.width, bat.height, MAGENTA, GOLD);
  }
};

int main()
{
  auto app = GameApp();
  InitWindow(Window::WIDTH, Window::HEIGHT, Window::TITLE);
  SetTargetFPS(60);

  // Setup Box2d
  // -----------------------------------------
  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);
  // -----------------------------------------

  while (!WindowShouldClose())
  {
    // Update
    // -----------------------------------------
    if (IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT))
      app.move_bat_right();
    if (IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressed(KEY_LEFT))
      app.move_bat_left();
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
