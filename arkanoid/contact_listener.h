#include <iostream>
#include "box2d/box2d.h"

class ArkanoidContactListner : public b2ContactListener
{
public:
  inline bool is_ball(b2Fixture *fx)
  {
    return (fx->GetShape()->GetType() == b2Shape::e_circle);
  }

  inline bool is_wall(b2Fixture *fx)
  {
    return (fx->GetShape()->GetType() == b2Shape::e_polygon && fx->GetBody()->GetType() == b2BodyType::b2_staticBody);
  }

  inline bool is_bat(b2Fixture *fx)
  {
    return (fx->GetShape()->GetType() == b2Shape::e_polygon && fx->GetBody()->GetType() == b2BodyType::b2_dynamicBody);
  }

  void BeginContact(b2Contact *contact)
  {
    // std::cout << "Collison detected " << std::endl;
    auto fxa = contact->GetFixtureA();
    auto fxb = contact->GetFixtureB();
    if (is_ball(fxa))
    {
      uintptr_t d = fxa->GetUserData().pointer;
      GameData *g = reinterpret_cast<GameData *>(d);
      std::cout << "fxa Ball data is: " << g->type << std::endl;
    }
    if (is_ball(fxb))
    {
      uintptr_t d = fxb->GetUserData().pointer;
      GameData *g = reinterpret_cast<GameData *>(d);
      std::cout << "fxb Ball data is: " << g->type << std::endl;
    }
  }
};
