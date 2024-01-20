#include "game_world.h"

GameWorld::GameWorld(b2World *w)
{
  world = w;
  create_game_box();
  create_ball();
}

void GameWorld::create_game_box()
{
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(300.0f, 392.0f);
  b2Body *ground_body = world->CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(300.0f, 2.0f);
  ground_body->CreateFixture(&ground_box, 0.0f);
  walls[0] = ground_body;

  b2BodyDef top_body_def;
  top_body_def.position.Set(300.0f, 8.0f);
  b2Body *top_body = world->CreateBody(&top_body_def);
  b2PolygonShape top_box;
  top_box.SetAsBox(300.0f, 2.0f);
  top_body->CreateFixture(&top_box, 0.0f);
  walls[1] = top_body;

  b2BodyDef left_body_def;
  left_body_def.position.Set(8.0f, 200.0f);
  b2Body *left_body = world->CreateBody(&left_body_def);
  b2PolygonShape left_box;
  left_box.SetAsBox(2.0f, 200.0f);
  left_body->CreateFixture(&left_box, 0.0f);
  walls[2] = left_body;

  b2BodyDef right_body_def;
  right_body_def.position.Set(592.0f, 200.0f);
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
  body_def.position.Set(50.0f, 40.0f);
  b2Body *body = world->CreateBody(&body_def);

  // b2PolygonShape dynamic_box;
  b2CircleShape dynamic_box;
  // dynamic_box.SetAsBox(1.0f, 1.0f);
  dynamic_box.m_radius = 2.0f;
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.5f;
  fixture_def.friction = 0.0f;
  fixture_def.restitution = 1.0f;
  body->CreateFixture(&fixture_def);
  body->SetBullet(true);
  ball = body;
}

void GameWorld::apply_force_to_ball()
{
  ball->ApplyForceToCenter(b2Vec2{5000000.0f, 6000000.0f}, true);
}

void GameWorld::draw()
{
  // Draw Ball
  auto ball_pos = ball->GetPosition();
  // std::cout << "Ball pos x: " << ball_pos.x << " pos y: " << ball_pos.y << std::endl;
  DrawCircle(ball_pos.x, ball_pos.y, 10.0f, MAROON);

  // Top
  DrawRectangle(0, 0, 600, 2, MAROON);
  // Bottom
  DrawRectangle(0, 398, 600, 2, MAROON);
  // Left
  DrawRectangle(0, 0, 2, 400, MAROON);
  // Right
  DrawRectangle(598, 0, 2, 400, MAROON);
}
