

#ifndef FSM_hpp
#define FSM_hpp

#include "cocos2d.h"
#include <memory>
#include "../model/Character.h"

class BaseFsm;

class State {
public:
    virtual void excute(cocos2d::Sprite* spr) = 0;
    virtual void PreProcess(cocos2d::Sprite* spr) = 0;
};

/*** 注意nullptr 的情况  ***/
class BaseFsm: public cocos2d::Node {
public:
    CREATE_FUNC(BaseFsm);
    virtual bool init();
    
    void changeState(std::shared_ptr<State> newstate) {_mCurState = newstate;}
    void update(float dt) override {if(_mCurState) _mCurState->excute(spr);}
private:
    std::shared_ptr<State> _mCurState;
    cocos2d::Sprite* spr;
};


#endif /* FSM_hpp */
