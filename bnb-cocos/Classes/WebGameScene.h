#pragma once

#include "cocos2d.h"
#include "Character.h"
#include "BnbGameClient.h"
#include "GameScene.h"
#include <vector>

/*
需要重构的函数 
1.init() 
需要创建其他角色（暂定一个）
2.CharacterMove()
<该函数需要重新定义>
在中间插入一段 向服务器发送位置的信息
服务器接收到后
向全体广播其位置信息
然后其他的client接受该信息
之后根据该信息调整非本client的chara的位置
用条件编译实现
3.update()
需要增加一个新的参数

需要新增的数据
1.GameClient client
客户端
2._other_num
存储其他的非本chara的角色个数

需要新增的函数
1.bool addCharacter(float x,float y,character::characterType Type);
新增个玩家
*/
class WebGameScene : public GameScene //必须继承它，部分函数需要重构
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();    
	//继承的GameScene里面，已经创建了一个_myplayer，该chara在本client操作
	//所以在这里添加的其他chara都是非本client的
	virtual void CharacterMove(character* chara , int flag);
	virtual void update(float dt) override;
	bool addCharacter(float x, float y, character::characterType Type);
	CREATE_FUNC(WebGameScene);
private:
	GameClient client;
	int _other_num;
};