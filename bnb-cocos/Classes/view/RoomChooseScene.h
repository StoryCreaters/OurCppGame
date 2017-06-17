#pragma once
#ifndef RoomChooseScene_hpp
#define RoomChooseScene_hpp
// 与web交互 选择房间的scene
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
#include "../web client/BnbGameClient.h"


extern "C" GameClient client;


using namespace cocos2d;
class RoomChoose : public cocos2d::Layer
{
public:
	/**
	* 静态函数，创建Scene场景
	* 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
	*/
	static cocos2d::Scene* createScene();
	/**
	* init函数，完成初始化操作。
	* 注意：init函数在Cocos2d-x中返回bool值，而不是返回Cocos2d-iPhone中的“id”
	*/
	virtual bool init();
	
	void update(float dt)override;
	/**
	* 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
	*/
	CREATE_FUNC(RoomChoose);
	//四个通往人物选择的函数
	void ToRoomOne(cocos2d::Ref* sender);
	void ToRoomTwo(cocos2d::Ref* sender);
	void ToRoomThree(cocos2d::Ref* sender);
	void ToRoomFour(cocos2d::Ref* sender);
private:
	Menu* UImenus = nullptr;
	int isOut;
};
#endif /* RoomChooseScene_hpp */
