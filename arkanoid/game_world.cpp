#include "game_world.h"

GameWorld::GameWorld(b2World *w)
{
  world = w;
  create_game_box();
  create_ball();
}

void GameWorld::create_game_box()
{
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(300.0f, 380.0f);
  b2Body *groundBody = world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(300.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
  game_bodies.push_back(groundBody);
}

void GameWorld::create_ball()
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(50.0f, 40.0f);
  b2Body *body = world->CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 50.0f;
  fixtureDef.friction = 0.3f;
  fixtureDef.restitution = 0.9f;
  body->CreateFixture(&fixtureDef);

  game_bodies.push_back(body);
}

void GameWorld::draw()
{
  // Game world decorations
  DrawRectangle(x_pos, y_pos, WIDTH, HEIGHT, bc);

  // Draw Ball
  auto ball_pos = game_bodies[1]->GetPosition();
  DrawCircle(ball_pos.x, ball_pos.y, 10.0f, WHITE);

  // Draw Ground
  DrawRectangle(0, 380, 600, 20, WHITE);
}

GameWorld::~GameWorld()
{
  for (auto &body : game_bodies)
  {
    world->DestroyBody(body);
  }
}
