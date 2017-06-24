﻿#include "CharacterSelect.h"
#include "Character.h"
#include "GameScene.h"
#include "RoomChooseScene.h"
#include "TextField.h"
#include "ChatBox.h"
#include "WebClient.h"
#include "SceneManager.h"
#include "../DataManager.h"

USING_NS_CC;
using namespace ui;

Scene* Players::createScene() {
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();
	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = Players::create();
	// 将GameSet层作为子节点添加到场景
	
    layer->setName("CharacterSelect");
    scene->addChild(layer);
	// 返回场景对象
	return scene;
}
// static function, GET CURRENT GAME SCENE
Players* Players::getCurrent() {
	auto currentScene = Director::getInstance()->getRunningScene();
	return dynamic_cast<Players*>(currentScene->getChildByName("Players"));
}
bool Players::init() {
	// 调用父类的init方法
    WebClient::getInstance()->cur_state = WebClient::CHARACTER_SELECT;
	if (!Layer::init()) {
		return false;
	}
	// 获得设备可见视图大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/temple of times.png");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	//Player1
	auto first_button = Button::create("GameUI/button.png");
	first_button->setScale(2);
	first_button->setTitleText("Player 1");
	first_button->setTitleFontName("Arial");
	first_button->setTitleFontSize(16);
	first_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.7));
	first_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			DataManager::getInstance()->setIntegerForKey("PLAYER", 1);
			int i = DataManager::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(first_button);
	//Player2
	auto second_button = Button::create("GameUI/button.png");
	second_button->setScale(2);
	second_button->setTitleText("Player 2");
	second_button->setTitleFontName("Arial");
	second_button->setTitleFontSize(16);
	second_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.50));
	second_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			DataManager::getInstance()->setIntegerForKey("PLAYER", 2);
			int i = DataManager::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(second_button);
	//Player3
	auto third_button = Button::create("GameUI/button.png");
	third_button->setScale(2);
	third_button->setTitleText("Player 3");
	third_button->setTitleFontName("Arial");
	third_button->setTitleFontSize(16);
	third_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.30));
	third_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			DataManager::getInstance()->setIntegerForKey("PLAYER", 3);
			int i = DataManager::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(third_button);
	//返回键
	auto return_button = Button::create("GameUI/b1.png");
	return_button->setPosition(Vec2(visibleSize.width *0.85, visibleSize.height*0.18));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到Room Choose场景
            SceneManager::toRoomSelect();
            WebClient::getInstance()->send_data("roomselect");
		}
	});
	this->addChild(return_button);
	//留白
    
    auto chatbox = ChatBox::create();
    chatbox->setName("ChatBox");
    addChild(chatbox);

    
	//设OK键
	auto ok_button = Button::create("GameUI/button1.png");
	ok_button->setPosition(Vec2(visibleSize.width *0.20, visibleSize.height*0.18));
	this->addChild(ok_button);
	ok_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
            auto s = "Start " + std::to_string(DataManager::getInstance()->getIntegerForKey("PLAYER"));
            WebClient::getInstance()->send_data(s);
            removeChild(ok_button);
			auto cancel_button = Button::create("GameUI/button2.png");
			cancel_button->setPosition(Vec2(visibleSize.width *0.20, visibleSize.height*0.18));
			this->addChild(cancel_button);
			// 切换到GameScene场景
//			auto transition = TransitionFadeBL::create(2.0, GameScene::createScene());
//			Director::getInstance()->replaceScene(transition);
		}
	});
	
	return true;
}
