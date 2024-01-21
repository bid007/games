#include <iostream>
#include "box2d/box2d.h"

class ArkanoidContactListner : public b2ContactListener
{
private:
  bool illegal_collision = false;
  b2Body *brick_body = nullptr;
  int score = 0;

public:
  bool game_end()
  {
    return illegal_collision;
  }

  b2Body *collision_brick()
  {
    b2Body *tmp = brick_body;
    brick_body = nullptr;
    return tmp;
  }

  int get_score()
  {
    return score;
  }

  void BeginContact(b2Contact *contact)
  {
    auto fxa = contact->GetFixtureA();
    auto fxb = contact->GetFixtureB();

    uintptr_t ptr_a = fxa->GetUserData().pointer;
    uintptr_t ptr_b = fxb->GetUserData().pointer;

    if (ptr_a == 0 || ptr_b == 0)
    {
      return;
    }

    GameData::BodyType body_a_type = reinterpret_cast<GameData *>(ptr_a)->type;
    GameData::BodyType body_b_type = reinterpret_cast<GameData *>(ptr_b)->type;

    // If one body type is 0 and other is 2, it must ball and ground
    if ((body_a_type | body_b_type) == 2)
    {
      illegal_collision = true;
    }

    if ((body_a_type & body_b_type) != 2)
      return;

    brick_body = (body_a_type == GameData::BRICK) ? fxa->GetBody() : fxb->GetBody();
    score += 1;
  }
};
