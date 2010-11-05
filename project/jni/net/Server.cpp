#include "Server.h"
#include "view/GameManager.h"
#include "levels/LevelsData.h"
#include "logic/Bomb.h"
#include "logic/Rocket.h"

Server* Server::instance = NULL;

void Server::handleConnect (const uint64_t& peerID) {

}

void Server::handleMsgHello (const uint64_t& peerID, size_t dataLen, const uint8_t* data, size_t offset) {
  zoobmsg::Hello hello;
  zoobmsg::Hello::unpack(dataLen, data, offset, hello);

  LOGI("[handleMsgHello] nickname=%s", (char*)hello.nickname.bytes);

  //Respond to hello by first sending version, then welcome message
  zoobmsg::Version version;
  version.version = PROTOCOL_VERSION;
  sendMsgVersion(peerID, version);

  zoobmsg::Welcome welcome;
  welcome.playerID = playerIDGen++;
  welcome.serverState = state;
  char* level = LevelManager::getInstance()->getLevel(GameManager::getInstance()->getCurrentLevel());
  size_t len = strlen(level)+1;
  welcome.level.numBytes = len;
  welcome.level.bytes = new char[len];
  strncpy(welcome.level.bytes, level, len);
  free(level);
  sendMsgWelcome(peerID, welcome);
}

void Server::handleMsgJoin (const uint64_t& peerID, size_t dataLen, const uint8_t* data, size_t offset) {
  zoobmsg::Join join;
  zoobmsg::Join::unpack(dataLen, data, offset, join);
}

void Server::handleMsgPlayerCommand (const uint64_t& peerID, size_t dataLen, const uint8_t* data, size_t offset) {
  zoobmsg::PlayerCommands commands;
  zoobmsg::PlayerCommands::unpack(dataLen, data, offset, commands);
}

void Server::handleDisconnect (const uint64_t& peerID) {
  
}

void Server::update(NetworkedGame& game) {
  //We want to read the GameState and broadcast it to clients
  //TODO
  zoobmsg::GameState state;
  const list<Tank*>* tanks = game.getTanks();

  state.numPlayerInfos = tanks->size();
  state.playerInfos = new zoobmsg::PlayerInfo[state.numPlayerInfos];

  int counter = 0;
  LIST_FOREACH_CONST(Tank*, (*tanks), i) {
    const Tank* tank = *i;

    zoobmsg::PlayerInfo* pinfo = &state.playerInfos[counter++];
    pinfo->playerID = tank->getID();
    pinfo->position.x = tank->getPosition().x;
    pinfo->position.y = tank->getPosition().y;
    pinfo->velocity.x = tank->getMoveDir().x;
    pinfo->velocity.y = tank->getMoveDir().y;

    pinfo->numRocketInfos = tank->getNumRockets();
    pinfo->rocketInfos = new zoobmsg::RocketInfo[pinfo->numRocketInfos];

    pinfo->numBombInfos = tank->getNumBombs();
    pinfo->bombInfos = new zoobmsg::BombInfo[pinfo->numBombInfos];

    int rCnt = 0;
    for (set<Rocket*>::const_iterator ri=tank->getRockets(); ri.hasNext(); ri++) {
      const Rocket* rocket = *ri;
      zoobmsg::RocketInfo& rInfo = pinfo->rocketInfos[rCnt++];
      rInfo.position.x = rocket->getPosition().x;
      rInfo.position.y = rocket->getPosition().y;
      rInfo.velocity.x = rocket->getDir().x;
      rInfo.velocity.y = rocket->getDir().y;
      rInfo.speed = rocket->getSpeed();
      rInfo.rocketID = rocket->getID();
    }

    int bCnt = 0;
    for (set<Bomb*>::const_iterator bi=tank->getBombs(); bi.hasNext(); bi++) {
      const Bomb* bomb = *bi;
      zoobmsg::BombInfo& bInfo = pinfo->bombInfos[bCnt++];
      bInfo.position.x = bomb->getPosition().x;
      bInfo.position.y = bomb->getPosition().y;
      bInfo.timeleft = bomb->getTimeLeft();
      bInfo.bombID = bomb->getID();
    }
  }

  //TODO:BROADCAST
}

void Server::sendPlayerCommand (uint16_t localPlayerID, const PlayerCommand& cmd) {
  //TODO
}



