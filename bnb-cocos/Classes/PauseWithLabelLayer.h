#ifndef PauseWithLabel_hpp
#define PauseWithLabel_hpp

#include "cocos2d.h"
#include <functional>

class PauseWithLabelLayer: public cocos2d::LayerColor {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();

    bool initialWithMenuVec(cocos2d::Vector<cocos2d::MenuItem*> &MenuToAdds);
    // a selector callback
//    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseWithLabelLayer);
    
//    CC_SYNTHESIZE_READONLY(cocos2d::Vector<cocos2d::MenuItem*>, _menuitems, MenuItems);
    
    void back(cocos2d::Ref* obj);
    // 根据MenuItems创建UI
    void addUI();
    cocos2d::Vector<cocos2d::MenuItem*> _menuitems;
    
    cocos2d::Layer* _parent;    //父层
    
    std::function<cocos2d::Layer*()> create_func;
private:
    cocos2d::EventListenerTouchOneByOne* _listener;
    
};

#endif /* PauseWithLabel_hpp */
