
struct GameData
{
  enum BodyType
  {
    TWALL = 0,
    BWALL,
    LWALL,
    RWALL,
    BALL,
    BAT,
    BRICK
  };
  /* data */
  BodyType type;
  GameData(BodyType t)
  {
    type = t;
  }
};
