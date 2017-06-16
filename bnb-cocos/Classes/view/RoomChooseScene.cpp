#include "RoomChooseScene.h"
#include "Character.h"
#include "GameScene.h"
#include "CharacterSelect.h"
#include "OpenScene.h"
#define NUM 4;
USING_NS_CC;
using namespace ui;

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

bool RoomChoose::init() {
	// 调用父类的init方法
	if (!Layer::init()) {
		return false;
	}
	// 获得设备可见视图大小
	vecs = { 0 };
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/GameOver.png");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//cocos2d::Vector<cocos2d::MenuItem*> vecs;

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
//void RoomChoose::ToRoomTwo(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}
//void RoomChoose::ToRoomThree(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}
//void RoomChoose::ToRoomFour(Ref *sender) {
//	Director::getInstance()->replaceScene(Players::createScene());
//}