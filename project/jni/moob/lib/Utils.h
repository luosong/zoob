#ifndef UTILS_H_
#define UTILS_H_

#include "Vector2.h"
#include "sys/time.h"

struct Utils {
  //Determine if point is inside the box determined by its top-left pos and width/height
  static bool inside (const Vector2& boxPos, float width, float height, const Vector2& p) {
    return (p.x > boxPos.x && p.x < boxPos.x+width) &&
            (p.y > boxPos.y && p.y < boxPos.y+height);
  }

  static long getCurrentTimeMillis () {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec/1000;
  }
};


#endif /* UTILS_H_ */
