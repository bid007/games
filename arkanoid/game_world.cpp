#include "game_world.h"

GameWorld::GameWorld(b2World *w)
{
  world = w;
  ground_id = new GameData(GameData::BWALL);
  bat_id = new GameData(GameData::BAT);
  ball_id = new GameData(GameData::BALL);
  brick_id = new GameData(GameData::BRICK);
  create_game_box();
  create_ball();
  create_bat();
}

void GameWorld::create_game_box()
{
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(300.0f, 398.0f);
  b2Body *ground_body = world->CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(300.0f, 2.0f);
  b2FixtureDef fixture;
  fixture.shape = &ground_box;
  fixture.userData.pointer = (uintptr_t)ground_id;
  ground_body->CreateFixture(&fixture);
  walls[0] = ground_body;

  b2BodyDef top_body_def;
  top_body_def.position.Set(300.0f, 4.0f);
  b2Body *top_body = world->CreateBody(&top_body_def);
  b2PolygonShape top_box;
  top_box.SetAsBox(300.0f, 2.0f);
  top_body->CreateFixture(&top_box, 0.0f);
  walls[1] = top_body;

  b2BodyDef left_body_def;
  left_body_def.position.Set(2.0f, 200.0f);
  b2Body *left_body = world->CreateBody(&left_body_def);
  b2PolygonShape left_box;
  left_box.SetAsBox(2.0f, 200.0f);
  left_body->CreateFixture(&left_box, 0.0f);
  walls[2] = left_body;

  b2BodyDef right_body_def;
  right_body_def.position.Set(598.0f, 200.0f);
  b2Body *right_body = world->CreateBody(&right_body_def);
  b2PolygonShape right_box;
  right_box.SetAsBox(2.0f, 200.0f);
  right_body->CreateFixture(&right_box, 0.0f);
  walls[3] = right_body;
}

void GameWorld::create_ball()
{
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position.Set(300.0f, 378.0f);
  b2Body *body = world->CreateBody(&body_def);

  b2CircleShape dynamic_box;
  dynamic_box.m_radius = 2.0f;
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 0.009f;
  fixture_def.friction = 0.0f;
  fixture_def.restitution = 1.0f;
  fixture_def.userData.pointer = (uintptr_t)ball_id;
  body->CreateFixture(&fixture_def);
  body->SetBullet(true);
  ball = body;
}

void GameWorld::create_bat()
{
  b2BodyDef bat_body_def;
  bat_body_def.type = b2_dynamicBody;
  bat_body_def.position.Set(300.0f, 390.0f);
  b2Body *bat_body = world->CreateBody(&bat_body_def);
  b2PolygonShape bat_box;
  bat_box.SetAsBox(40.0f, 10.0f);
  b2FixtureDef fixture;
  fixture.shape = &bat_box;
  fixture.density = 0.01f;
  fixture.userData.pointer = (uintptr_t)bat_id;
  bat_body->CreateFixture(&fixture);
  bat = bat_body;
}

void GameWorld::move_bat()
{
  if (IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT))
  {
    bat->ApplyForceToCenter(b2Vec2{100000.0f, -100.0f}, true);
  }

  if (IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressed(KEY_LEFT))
  {
    bat->ApplyForceToCenter(b2Vec2{-100000.0f, -100.0f}, true);
  }
  if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
  {
    bat->SetAwake(false);
  }
}

void GameWorld::apply_force_to_ball()
{
  srand(time(NULL));
  auto r = rand() % 2;
  float m = (r == 1) ? -1 : 1;
  ball->ApplyForceToCenter(b2Vec2{5000000.0f * m, 6000000.0f}, true);
}

void GameWorld::draw()
{
  // Draw bounding box
  // ------------------------------------
  // Top
  DrawRectangleGradientH(0, 0, 600, 4, GREEN, RED);
  // Bottom
  DrawRectangleGradientH(0, 396, 600, 4, GREEN, RED);
  // Left
  DrawRectangleGradientV(0, 0, 4, 400, GREEN, MAROON);
  // Right
  DrawRectangleGradientV(596, 0, 4, 400, GREEN, MAROON);
  // ------------------------------------

  // Draw Ball
  auto ball_pos = ball->GetPosition();
  DrawCircle(ball_pos.x, ball_pos.y, 10.0f, MAROON);
  DrawCircleLines(ball_pos.x, ball_pos.y, 10.0f, WHITE);

  // Draw Bat
  auto bat_pos = bat->GetPosition();
  DrawRectangleGradientH(bat_pos.x - 40, bat_pos.y - 10, 80, 20, MAGENTA, LIME);
  DrawRectangleLines(bat_pos.x - 40, bat_pos.y - 10, 80, 20, WHITE);
}

GameWorld::~GameWorld()
{
  delete ground_id;
  delete bat_id;
  delete ball_id;
  delete brick_id;
}
