#include "Game.h"
#include "lib/Math.h"
#include "ai/movement/StillPolicy.h"
#include "ai/shoot/RandomPolicy.h"
#include "ai/shoot/AimPolicy.h"
#include "logic/GreenTank.h"
#include "logic/RedTank.h"

Game::Game (game_over_callback_t goCallback, Level* level)
    : colManager(level->getWidth(), level->getHeight(), 1.0f),
      tank(),
      level(level),
      elapsedS(0),
      movingState(MOVING_NONE),
      gameOverCallback(goCallback) {
  level->addToColManager(colManager);
  tank.setPosition(level->getStartPosition());
  colManager.addEntity(&tank);

  playerMaxLives = 2;
  playerNumLives = playerMaxLives;

  //Spawn enemies
  for (unsigned x=0; x<level->getWidth(); x++) {
    for (unsigned y=0; y<level->getHeight(); y++) {
      Tile* tile = level->getTile(x,y);
      if (tile->getType() == _1) {
        RedTank* t = new RedTank();
        t->setPosition(Vector2(x,y));
        enemies.append(t);
        colManager.addEntity(t);
      } else if (tile->getType() == _2) {
        GreenTank* t = new GreenTank();
        t->setPosition(Vector2(x,y));
        enemies.append(t);
        colManager.addEntity(t);
      }
    }
  }

  lastTime = Utils::getCurrentTimeMillis();
}

Game::~Game () {
  LIST_FOREACH(EnemyTank*, enemies, i)
    delete *i;
}

void Game::update () {
  uint64_t now = Utils::getCurrentTimeMillis();
  //Do nothing if lastTime is in the future
  //This allows the game start (and unpause) to delay
  //the start of the physics by 100ms or whatever
  if (lastTime > now) {
    LOGE("lastTime(%lu) > now(%lu)", (unsigned long)lastTime, (unsigned long)now);
    return;
  }

  explosions.clear();

  elapsedS = (now-lastTime)/1000.0;
  lastTime = now;

  if (Math::epsilonEq(elapsedS, 0))
    return;

  colManager.unmarkCollided();

  //Rockets
  for (list<Rocket*>::iterator i = rockets.begin(); i.hasNext(); ) {
    Rocket* r = *i;
    if (!r->hasExploded() && (r->getNumBounces() > 3)) {
      r->explode(NULL, r->getPosition());
      explosions.append(r->getPosition());
    }
    //Might have exploded because of num bounces OR because of collision
    if (r->hasExploded()) {
      colManager.removeEntity(*i);
      delete (*i);
      i = rockets.remove(i);
    } else {
      bounceMove(r, r->getDir()*ROCKET_MOVE_SPEED*elapsedS);
      i++;
    }
  }

  //Enemies
  LIST_FOREACH(EnemyTank*, enemies, i) {
    EnemyTank* t = *i;
    if (!t->isAlive())
      continue;

    if (t->hasExploded()) {
      colManager.removeEntity(t);
      t->die();
    } else {
      TankAI* ai = t->getAI();
      if (ai) {
        doTankMove(t, ai->decideDir(elapsedS, this, t), elapsedS);
        Vector2 rocketDir;
        if (t->canFire() && ai->decideFire(elapsedS, &rocketDir, this, t)) {
          rockets.append(t->fireRocket(rocketDir));
        }
        Vector2 aim;
        if (ai->aim(elapsedS, this, t, &aim))
          t->setRotationFromDir(aim.getNormalized());
      }
    }
  }

  if (tank.hasExploded()) {
    playerNumLives--;
    tank.unmarkExploded();
    LOGE("playerNumLives : %i", playerNumLives);
    if (playerNumLives == 0) {
      gameOverCallback();
    }
  }

  //Player Tank movement
  if (isMovingTank()) {
    Vector2 dir = getTankMoveDir();
    doTankMove(&tank, dir, elapsedS);

    /*CollisionResult r;
    if (colManager.trace(&tank, move, &r)) {
      r.collidedEntity->collided = true;
      tank.collided  = true;
      tank.lastColNormal = r.normal;
      tank.lastColPoint = r.colPoint;
      //LOGE("tFirst: %f, tLast: %f, normal: (%f,%f) colPoint (%f,%f)", r.tFirst, r.tLast, r.normal.x, r.normal.y, r.colPoint.x, r.colPoint.y);
    }*/
  }
}

void Game::doTankMove (Tank* t, Vector2 dir, double elapsedS) {
  if (dir.length() == 0)
    return;

  dir.normalize();
  tank.setRotationFromDir(dir);

  const Vector2 move = dir*TANK_MOVE_SPEED*elapsedS;
  slideMove(&tank, move);
}

void Game::startMoving (eMoveState what, const Vector2& touchPosition) {
  movingState = what;
  switch(movingState) {
    case MOVING_TANK_PAD:
    case MOVING_TANK:
      tankMoveEnd = touchPosition;
      break;
    case MOVING_CURSOR:
      cursor.setPosition(touchPosition);
      break;
    case MOVING_TANK_EDGES:
      //edgeMoveDir = touchPosition;
      tankMoveEnd = touchPosition;
      break;
    default:
      break;
  }
}

void Game::setMoveTouchPoint (const Vector2& pos) {
  switch (movingState) {
    case MOVING_TANK:
    case MOVING_TANK_PAD:
      tankMoveEnd = pos;
      break;
    case MOVING_CURSOR:
      cursor.setPosition(pos);
      break;
    case MOVING_TANK_EDGES:
      edgeMoveDir = pos;
      tankMoveEnd = pos;
      break;
    default:
      break;
  }
}

void Game::stopMoving () {
  if (movingState == MOVING_CURSOR) {
    //Fire up rocket
    if (tank.canFire()) {
      Vector2 dir = cursor.getPosition()-tank.getPosition();
      dir.normalize();
      rockets.append(tank.fireRocket(dir));
    }
  }
  movingState = MOVING_NONE;
}

void Game::touch (Entity* e1, Entity* e2, const Vector2& colPoint) {
  const eEntityType t1 = e1->getType();
  const eEntityType t2 = e2->getType();
  //tank-wall and tank-tank
  if ((t1 == ENTITY_TANK || t1 == ENTITY_WALL) &&
      (t2 == ENTITY_TANK || t2 == ENTITY_WALL))
    return;
  //rocket-wall
  if ((t1 == ENTITY_ROCKET && t2 == ENTITY_WALL) ||
      (t2 == ENTITY_ROCKET && t1 == ENTITY_WALL))
    return;

  e1->explode(e2, colPoint);
  e2->explode(e1, colPoint);

  explosions.append(colPoint);
}

void Game::bounceMove (Rocket* rocket, Vector2 move) {
  CollisionResult r;
  if (colManager.trace(rocket, move, &r)) {
    if (!r.collidedEntity->bounce(rocket, r.colPoint))
      touch(rocket, r.collidedEntity, r.colPoint);
    rocket->addBounce();
    move = -2.0f*(move*r.normal)*r.normal + move;
    rocket->setDir(move);
  }
  colManager.translate(rocket, move);
}

#define MAX_BOUNCES 4
void Game::slideMove (Entity* e, Vector2 move) {
  //Used to store the backoffs of previous iterations, so we don't go
  //against a backoff we've already taken into account
  Vector2 backoffs[MAX_BOUNCES];

  CollisionResult r;
  for (size_t bounces = 0; colManager.trace(e, move, &r) && (bounces < MAX_BOUNCES); bounces++) {
    touch(e, r.collidedEntity, r.colPoint);

    const Vector2 newPos = e->getPosition()+move;
    float backAmount = (r.colPoint - newPos)*r.normal;
    Vector2 backoff = backAmount*r.normal;
    move += backoff*1.1;

    //Check that we aren't going against a previous backoff
    for (size_t j=0; j<bounces; j++) {
      //if cos(angle between move and backoff) is in [0,1], we have an angle between
      //-90 and 90
      //cos = (vel*normals[i]/(||vel||*||normals[i]||)
      //but since we only care about the sign of the cos, we can forget division
      if (move*backoffs[j] >= 0)
        continue;

      //If we reach this point, we're going against backoffs[j], just add it once more to correct this
      move += backoffs[j];

      //Check that our new corrected move doesn't go AGAIN against another previous backoff
      for (size_t k=0; k<bounces; k++) {
        if (k==j)
          continue;

        if (move*backoffs[k] >= 0)
          continue;

        //LOGE("Unable to find a way out!");
        //We're going against 2 previous backoff, just cancel the move
        move.set(0,0);
      }
    }

    backoffs[bounces] = backoff;
  }
  colManager.translate(e, move);
}
