#include "box2d/box2d.h"
#include <iostream>

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
    std::cout << "Collison detected " << std::endl;
    auto fxa = contact->GetFixtureA();
    auto fxb = contact->GetFixtureB();

    if ((is_wall(fxa) && is_bat(fxb)) || (is_wall(fxb) && is_bat(fxa)))
    {
      std::cout << "Bat and wall collided" << std::endl;
      if (is_bat(fxa))
      {
        fxa->GetBody()->SetAwake(false);
      }
      else
      {
        fxb->GetBody()->SetAwake(false);
      }
    }
  }
};
