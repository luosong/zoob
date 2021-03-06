#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "def.h"
#include "lib/Vector2.h"
#include "Sprite.h"
#include "logic/Game.h"
#include "Animation.h"

class Explosion {
  public:
    Explosion (const ExplosionLocation& loc);

    void drawLighting ();
    void draw ();

    //think should be called BEFORE any draw functions
    void think (float elapsed) {
      timeLeft -= elapsed;
      this->elapsed = elapsed;
    }

    float getTimeLeft () {
      return timeLeft;
    }

  private:
    float elapsed;
    float timeLeft;
    //Sprite boomSprite;
    Sprite poofSprite;
    Sprite explLight;
    Animation fireExpl;
    const ExplosionLocation location;
};

#endif /* EXPLOSION_H_ */
