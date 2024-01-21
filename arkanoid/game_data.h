
struct GameData
{
  enum BodyType
  {
    BWALL = 0,
    BAT,
    BALL,
    BRICK
  };
  /* data */
  BodyType type;
  GameData(BodyType t)
  {
    type = t;
  }
};
