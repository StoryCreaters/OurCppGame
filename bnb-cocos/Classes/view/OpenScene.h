#ifndef OpenScene_hpp
#define OpenScene_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"


using namespace cocos2d;

class OpenScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void SwitchToOpen(cocos2d::Ref* pSender);

	cocos2d::Menu* setLayOutL1();
	void musicOnAndOff(cocos2d::Ref* pSender);

	CREATE_FUNC(OpenScene);

	void GameSetting(cocos2d::Ref* pSender);
	void OnTouchPause(cocos2d::Ref* pSender);
	void OnTouchResume();
	void ToStartInGame(cocos2d::Ref* sender);

	// debug
	void sceneTest(Ref *sender);
private:
	Menu* UImenus = nullptr;
};


#endif /* OpenScene_hpp */