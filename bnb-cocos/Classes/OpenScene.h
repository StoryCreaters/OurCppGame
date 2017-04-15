#ifndef OpenScene_hpp
#define OpenScene_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class OpenScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);    
    void SwitchToOpen( cocos2d::Ref* pSender);

    cocos2d::Menu* setLayOutL1();
    cocos2d::Menu* setMusicLine(const std::string &music_name);
    // implement the "static create()" method manually
    void musicOnAndOff(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(OpenScene);
};


#endif /* OpenScene_hpp */
