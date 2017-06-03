#pragma once

#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__ 

#include "cocos2d.h" 

class GameSettings : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuOkCallback(cocos2d::Ref* pSender);
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuQuickItemCallback(cocos2d::Ref* pSender);
	void menuNormalItemCallback(cocos2d::Ref* pSender);
	void menuSlowItemCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameSettings);
};


#endif // __SettingScene_SCENE_H__
