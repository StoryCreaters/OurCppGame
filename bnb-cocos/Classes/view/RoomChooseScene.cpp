﻿#include "RoomChooseScene.h"
#include "../model/Character.h"
#include "GameScene.h"
<<<<<<< .merge_file_a93180
#include "CharacterSelect.h"
<<<<<<< HEAD
#include "../web client/BnbGameClient.h"
=======
#include "OpenScene.h"
#include "CharacterSelect.h"

>>>>>>> .merge_file_a16140

=======
#include "OpenScene.h"
#define NUM 4;
>>>>>>> fcc15ea0b861a694da535b3682b217526dacad50
USING_NS_CC;
using namespace ui;

<<<<<<< .merge_file_a93180
=======
static Size visibleSize;
std::vector <RoomInfo> Rooms;  //房间列表
GameClient client;  
extern struct PlayerInfo myPlayerInfo;
int whichRoom;
>>>>>>> .merge_file_a16140
Scene* RoomChoose::createScene() {
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();
	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = RoomChoose::create();
	// 将GameSet层作为子节点添加到场景
	scene->addChild(layer);
	// 返回场景对象
	return scene;
}

<<<<<<< .merge_file_a93180
GameClient client;
=======

>>>>>>> .merge_file_a16140

bool RoomChoose::init() {
	// 调用父类的init方法
	if (!Layer::init()) {
		return false;
	}

	//网络初始化
	client.init();

<<<<<<< .merge_file_a93180

	// 获得设备可见视图大小
	vecs = { 0 };
	Size visibleSize = Director::getInstance()->getVisibleSize();
<<<<<<< HEAD
	auto backGround = cocos2d::Sprite::create("BackGround/Gray World.jpg");
=======
	isOut = false;

	visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/chooseroom.png");
>>>>>>> .merge_file_a16140
=======
	auto backGround = cocos2d::Sprite::create("BackGround/GameOver.png");
>>>>>>> fcc15ea0b861a694da535b3682b217526dacad50
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

<<<<<<< HEAD
<<<<<<< .merge_file_a93180
	cocos2d::Vector<cocos2d::MenuItem*> vecs;

	std::string UiNames[] = { "GameUI/RoomChoose", "GameUI/Room1", "GameUI/Room2", "GameUI/Room3","GameUI/Room4"};
=======

	cocos2d::Vector<cocos2d::MenuItem*> vecs;
	std::string UiNames[] = { "GameUI/RoomChoose", "GameUI/Room1", "GameUI/Room2", "GameUI/Room3","GameUI/Room4" };
>>>>>>> .merge_file_a16140
	ccMenuCallback Uifuncs[] = { nullptr,CC_CALLBACK_1(RoomChoose::ToRoomOne, this), CC_CALLBACK_1(RoomChoose::ToRoomTwo, this),CC_CALLBACK_1(RoomChoose::ToRoomThree, this),CC_CALLBACK_1(RoomChoose::ToRoomFour, this) };
	for (int i = 0; i < 5; ++i) {
		auto menuI = cocos2d::MenuItemImage::create(UiNames[i] + ".png", UiNames[i] + "Selected.png", Uifuncs[i]);
		if (i != 0)
			menuI->setScale(0.8, 0.6);
		vecs.pushBack(menuI);
	}
<<<<<<< .merge_file_a93180
	for (int i=0; i < 4; i++) {
		LabelTTF* label;
		label = LabelTTF::create("Number:", "微软雅黑", 32);
		label->setColor(Color3B::BLACK);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.8, visibleSize.height*0.62-i*115));
=======
	LabelTTF* label_1;
	label_1 = LabelTTF::create("Room Name:", "Arial", 32);
	label_1->setColor(Color3B::BLACK);
	label_1->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.73 - 15));
	this->addChild(label_1);
	//房间人数
	auto * label = LabelTTF::create("Current Players", "Arial", 32);
	label->setColor(Color3B::BLACK);
	label->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 70, visibleSize.height*0.73 - 15));
	addChild(label);
	for (int i = 0; i < 4; i++) {
		LabelTTF* label;
		//把这里的Number实现成现有人数
		label = LabelTTF::create("		/4", "微软雅黑", 32);
		label->setColor(Color3B::BLACK);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 100, visibleSize.height*0.62 - i * 115));
>>>>>>> .merge_file_a16140
		this->addChild(label);
	}

	UImenus = cocos2d::Menu::createWithArray(vecs);
	UImenus->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	UImenus->alignItemsVertically();
	addChild(UImenus);
<<<<<<< .merge_file_a93180


	this->schedule(schedule_selector(RoomChoose::update), 3.0); //每3s更新一次人数信息

=======
	//房间编号
	auto * label_2 = LabelTTF::create("Room Number:", "Arial", 32);
	label_2->setColor(Color3B::BLACK);
	label_2->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height*0.73 - 15));
	addChild(label_2);
	for (int i = 0; i < 4; i++) {
		LabelTTF* label;
		char str[5];
		int j = 1000 + i;
		itoa(j, str, 10);
		label = LabelTTF::create(str, "微软雅黑", 32);
		label->setColor(Color3B::BLACK);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height*0.62 - i * 115));
		this->addChild(label);
	}
	// 创建“返回“按钮，点击时调用returnToMenu函数
	auto return_button = Button::create("GameUI/b1.png");
	return_button->setPosition(Vec2(visibleSize.width *0.85, visibleSize.height*0.18 - 100));
	return_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到MenuScene场景
			auto transition = TransitionShrinkGrow::create(2.0, OpenScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);

	auto curTotalNum = LabelTTF::create("Online Players:", "Arial", 24);
	curTotalNum->setColor(Color3B::BLACK);
	curTotalNum->setPosition(cocos2d::Vec2(visibleSize.width - 850, visibleSize.height - 50));
	this->addChild(curTotalNum);

	this->scheduleUpdate(); //每一帧更新一次人数信息
>>>>>>> .merge_file_a16140
=======
	//cocos2d::Vector<cocos2d::MenuItem*> vecs;
>>>>>>> fcc15ea0b861a694da535b3682b217526dacad50

	auto headline = Sprite::create("GameUI/RoomChoose.png");
	headline->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.75));
	backGround->addChild(headline);
	auto room_button = Button::create("GameUI/RoomCreate.png");
	room_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	room_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到Character Select场景
			auto transition = TransitionShrinkGrow::create(2.0, Players::createScene());
			Director::getInstance()->replaceScene(transition);
			if (vecs.back() < 4) {
				vecs.back()++;
			}
			else
				addroom(this);
		}
	});
	addChild(room_button);
	// 创建“返回“按钮，点击时调用returnToMenu函数
	auto return_button = Button::create("GameUI/b1.png");
	return_button->setPosition(Vec2(visibleSize.width *0.85, visibleSize.height*0.18));
	return_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到MenuScene场景
			auto transition = TransitionShrinkGrow::create(2.0, OpenScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);
	return true;
}

void RoomChoose::ToRoomOne(Ref *sender) {
<<<<<<< .merge_file_a93180
	Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::addroom(Ref* sender) {
	if (!vecs.empty()) {
		vecs.push_back(1);
		log("vecs[i]=%d", vecs.back());
	}
}
void RoomChoose::poproom( Ref* sender) {
	if (!vecs.empty()) {
		vecs.back()--;
	}
	
}
<<<<<<< HEAD
void RoomChoose::ToRoomFour(Ref *sender) {
	Director::getInstance()->replaceScene(Players::createScene());
}


/*
名称：更新
描述：每3秒更新一次人数信息
*/
void RoomChoose::update(float dt)
{
	int val;
	std::string msg = "Current number of people online：" + std::to_string(val);
	auto * label = LabelTTF::create(msg, "Arial", 32);
	label->setPosition(100, 100);
=======
	isOut = true;
	client.clientProcessBefore(isOut,0);
	//Rooms[0].playerList.push_back(myPlayerInfo);
	Rooms[0].curNum++;
	whichRoom = 0;
	Director::getInstance()->replaceScene(Players::createScene(0));
}

void RoomChoose::ToRoomTwo(Ref *sender) {
	isOut = true;
	client.clientProcessBefore(isOut,1);
	//Rooms[1].playerList.push_back(myPlayerInfo);
	Rooms[1].curNum++;
	whichRoom = 1;
	Director::getInstance()->replaceScene(Players::createScene(1));
}

void RoomChoose::ToRoomThree(Ref *sender) {
	isOut = true;
	client.clientProcessBefore(isOut,2);
	//Rooms[2].playerList.push_back(myPlayerInfo);
	Rooms[2].curNum++;
	whichRoom = 2;
	Director::getInstance()->replaceScene(Players::createScene(2));
}

void RoomChoose::ToRoomFour(Ref *sender) {
	isOut = true;
	client.clientProcessBefore(isOut,3);
	//Rooms[3].playerList.push_back(myPlayerInfo);
	Rooms[3].curNum++;
	whichRoom = 3;
	Director::getInstance()->replaceScene(Players::createScene(3));
}


/*
名称：更新
描述：每帧更新一次人数信息
*/
void RoomChoose::update(float dt)
{
	//TODO 房间的名字是Rooms[i].name  房间号是 Room[i].id  房间人数是Room[i].curNum 额定最大人数是4人
	static LabelTTF * label;
	static LabelTTF * label1;   //房间一的人数
	static LabelTTF * label2;   //房间二的人数
	static LabelTTF * label3;   //房间三的人数
	static LabelTTF * label4;   //房间四的人数

	removeChild(label);
	removeChild(label1);
	removeChild(label2);
	removeChild(label3);
	removeChild(label4);

	int val = client.clientProcessBefore(isOut,-1);

	std::string msg = std::to_string(val);
	std::string msg1 = std::to_string(Rooms[0].curNum);
	std::string msg2 = std::to_string(Rooms[1].curNum);
	std::string msg3 = std::to_string(Rooms[2].curNum);
	std::string msg4 = std::to_string(Rooms[3].curNum);

	label = LabelTTF::create(msg, "Arial", 32);
	label->setColor(Color3B::BLACK);
	label->setPosition(cocos2d::Vec2(visibleSize.width - 750, visibleSize.height - 50));
	addChild(label);


	
	label1 = LabelTTF::create(msg1, "Arial", 32);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 65, visibleSize.height*0.62 - 0 * 115));
	addChild(label1);
	
	label2 = LabelTTF::create(msg2, "Arial", 32);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 65, visibleSize.height*0.62 - 1 * 115));
	addChild(label2);
	
	label3 = LabelTTF::create(msg3, "Arial", 32);
	label3->setColor(Color3B::BLACK);
	label3->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 65, visibleSize.height*0.62 - 2 * 115));
	addChild(label3);

	label4 = LabelTTF::create(msg4, "Arial", 32);
	label4->setColor(Color3B::BLACK);
	label4->setPosition(cocos2d::Vec2(visibleSize.width *0.8 + 65, visibleSize.height*0.62 - 3 * 115));
	addChild(label4);
	

>>>>>>> .merge_file_a16140
}
=======
//void RoomChoose::ToRoomTwo(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}
//void RoomChoose::ToRoomThree(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}
//void RoomChoose::ToRoomFour(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}
>>>>>>> fcc15ea0b861a694da535b3682b217526dacad50
