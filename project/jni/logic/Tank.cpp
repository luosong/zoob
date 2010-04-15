#include "Tank.h"
#include "Rocket.h"

Rocket* Tank::fireRocket (Vector2 dir) {
  ASSERT(dir.length() > 0);
  dir.normalize();
  //Have to spawn the rocket just outside of our bounding box
  const Vector2 trans = dir*ROCKET_BCIRCLE_R + dir*TANK_BCIRCLE_R;
  setRotationFromDir(dir);
  lastFireTime = Utils::getCurrentTimeMillis();
  return new Rocket(this, getPosition()+trans*1.1, dir);
}
