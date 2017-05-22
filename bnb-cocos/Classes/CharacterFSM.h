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
    void changeTo();
};

// the state shows move, have directions
class CharMoveState: public state{
public:
    CharMoveState(settings::directions in_direc): direc(in_direc) {}
    void excute(cocos2d::Sprite* spr) override;
//    void setAnime() override;
private:
    settings::directions direc;
};

class CharStandState: public state{
public:
    void excute(cocos2d::Sprite* spr) override;
//    void setAnime() override;
};

class CharToDieState: public state {
public:
    void excute(cocos2d::Sprite* spr) override;
//    void setAnime() override;
};

#endif /* characterFSM_hpp */
