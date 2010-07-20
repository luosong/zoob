#ifndef LEVELSDATA_H_
#define LEVELSDATA_H_

#include "logic/Level.h"

Level* loadAPKLevel (int levelNum);
void loadSerie(const char* serieJSON);
size_t getNumLevels ();

#endif /* LEVELSDATA_H_ */
