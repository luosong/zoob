#ifndef TANKVIEW_H_
#define TANKVIEW_H_

#include "logic/Tank.h"
#include "Sprite.h"
#include "GLW.h"

class TankView {
  public:
    TankView (const Tank& t) :
      tank(t),
      tankSprite("assets/sprites/tank1.png"),
      shieldTankSprite("assets/sprites/tank_shield.png") {
    }

     // Return the display color for the given tank (depends on tanktype)
    static eColor getColor (eTankType type) {
      switch(type) {
        case TANK_PLAYER: return GREEN;
        case TANK_SIMPLE: return RED;
        case TANK_SHIELD: return ORANGE;
        case TANK_STATIC: return GREY;
        case TANK_BURST: return VIOLET;
        default: LOGE("Unhandled tank type : %i", type); return WHITE;
      }
    }

    virtual void draw () {
      if (!tank.isAlive())
        return;
      eTankType type = tank.getTankType();
      GLW::color(getColor(type));
      switch(type) {
        case TANK_PLAYER:
        case TANK_STATIC:
        case TANK_SIMPLE:
        case TANK_BURST:
          tankSprite.draw(tank, tank.getRotation(), getTankScale());
          break;
        case TANK_SHIELD:
          shieldTankSprite.draw(tank, tank.getRotation(), getTankScale());
          break;
      }
      GLW::colorWhite();
    }

    virtual float getTankScale () { return 1.0f; }

    Vector2 getCenter () {
      return tankSprite.getCenter(tank);
    }

    bool touchInside (const Vector2& p) const {
      return tankSprite.touchInside(tank, p);
    }
  protected:
    const Sprite& getTankSprite () { return tankSprite; }
    const Sprite& getShieldTankSprite () { return shieldTankSprite; }
  private:
    const Tank& tank;
    Sprite tankSprite;
    Sprite shieldTankSprite;

};

#endif /* TANKVIEW_H_ */
