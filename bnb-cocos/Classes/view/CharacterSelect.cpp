#include "CharacterSelect.h"
#include "../model/Character.h"
#include "GameScene.h"
#include "RoomChooseScene.h"
#include "TextField.h"
#include "ChatBox.h"
#include "../web client/BnbGameClient.h"


USING_NS_CC;
using namespace ui;

Scene* Players::createScene() {
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();
	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = Players::create();
	// 将GameSet层作为子节点添加到场景
	scene->addChild(layer);
	// 返回场景对象
	return scene;
}
// static function, GET CURRENT GAME SCENE
Players* Players::getCurrent() {
	auto currentScene = Director::getInstance()->getRunningScene();
	return dynamic_cast<Players*>(currentScene->getChildByName("Players"));
}


extern "C" GameClient client;


bool Players::init() {
	// 调用父类的init方法
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
	first_button->setTitleFontName("微软雅黑");
	first_button->setTitleFontSize(16);
	first_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.7));
	first_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			UserDefault::getInstance()->setIntegerForKey("PLAYER", 1);
			int i = UserDefault::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(first_button);
	//Player2
	auto second_button = Button::create("GameUI/button.png");
	second_button->setScale(2);
	second_button->setTitleText("Player 2");
	second_button->setTitleFontName("微软雅黑");
	second_button->setTitleFontSize(16);
	second_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.50));
	second_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			UserDefault::getInstance()->setIntegerForKey("PLAYER", 2);
			int i = UserDefault::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(second_button);
	//Player3
	auto third_button = Button::create("GameUI/button.png");
	third_button->setScale(2);
	third_button->setTitleText("Player 3");
	third_button->setTitleFontName("微软雅黑");
	third_button->setTitleFontSize(16);
	third_button->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.30));
	third_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 存值
			UserDefault::getInstance()->setIntegerForKey("PLAYER", 3);
			int i = UserDefault::getInstance()->getIntegerForKey("PLAYER");
		}
	});
	this->addChild(third_button);
	//返回键
	auto return_button = Button::create("GameUI/b1.png");
	return_button->setPosition(Vec2(visibleSize.width *0.85, visibleSize.height*0.18));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到Room Choose场景
			auto transition = TransitionShrinkGrow::create(2.0, RoomChoose::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);
	//留白
    addChild(ChatBox::create());
//	auto layerColor = LayerColor::create(Color4B(41, 36, 33, 200), 400, 400);
//	layerColor->setPosition(208, 150);
//	this->addChild(layerColor);
//	auto textfield = TextFieldTest::create();
//	textfield->setName("TextField");
//	addChild(textfield);
	//设OK键
	auto ok_button = Button::create("GameUI/button1.png");
	ok_button->setPosition(Vec2(visibleSize.width *0.20, visibleSize.height*0.18));
	this->addChild(ok_button);
	ok_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			removeChild(ok_button);
			auto cancel_button = Button::create("GameUI/button2.png");
			cancel_button->setPosition(Vec2(visibleSize.width *0.20, visibleSize.height*0.18));
			this->addChild(cancel_button);
			// 切换到GameScene场景
			auto transition = TransitionFadeBL::create(2.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	
	

	return true;
}
