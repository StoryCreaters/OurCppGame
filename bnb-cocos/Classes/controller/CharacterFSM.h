/*
 fsm & State
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



class CharNormal : public State {
public:
    void excute(cocos2d::Sprite* spr) override;
    void PreProcess(cocos2d::Sprite* spr) override {};
};

class CharStuck : public State {
public:
    void excute(cocos2d::Sprite* spr) override;
    void PreProcess(cocos2d::Sprite* spr) override;
};

class CharDead : public State {
public:
    void excute(cocos2d::Sprite* spr) override {}
    void PreProcess(cocos2d::Sprite* spr) override;
};

#endif /* characterFSM_hpp */
