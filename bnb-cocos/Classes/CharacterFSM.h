/*
 fsm & state
 move(4), stand(4), ToDie, Die
 */

#ifndef characterFSM_hpp
#define characterFSM_hpp

#include "cocos2d.h"
#include "BaseFSM.h"
#include "Settings.h"



class CharacterFSM: public BaseFsm {
public:
    void Move(settings::directions dir);
    void Stand();
    // 变成垂死的泡泡
    void ToDie();
};

#endif /* characterFSM_hpp */
