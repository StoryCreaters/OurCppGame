#include "OpenScene.h"
#include "PauseWithLabelLayer.h"
#include "ToStart.h"
#include "GameScene.h"
#include "MusicSetting.h"
#include "RoomChooseScene.h"
#include "CharacterSelect.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
//float Volume=1.0;
Scene* OpenScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OpenScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void OpenScene::musicOnAndOff(cocos2d::Ref* pSender) {
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	static int times = 0;
	if (times++ % 2 == 0) {
		audio->pauseBackgroundMusic();
	}
	else
		audio->resumeBackgroundMusic();
}

// on "init" you need to initialize your instance
bool OpenScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto backGround = cocos2d::Sprite::create("BackGround/Gray World.jpg");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);


	auto menu_list = setLayOutL1();
	addChild(menu_list);
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume = UserDefault::getInstance()->getFloatForKey("musicPercent");
	audio->setBackgroundMusicVolume(volume);
	audio->playBackgroundMusic("music/When The Morning Comes.mp3", true);
	return true;
}

cocos2d::Menu* OpenScene::setLayOutL1() {
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	cocos2d::Vector<cocos2d::MenuItem*> vecs;

	std::string UiNames[] = {
        "GameUI/ProjectName",
        "GameUI/PlayOnInternet",
        "GameUI/Help",
        "GameUI/Setting",
        "GameUI/Quit"
    };
    
	ccMenuCallback Uifuncs[] = {
        nullptr,
        CC_CALLBACK_1(OpenScene::ToLogIn, this),
        CC_CALLBACK_1(OpenScene::OnTouchPause, this),
        CC_CALLBACK_1(OpenScene::GameSetting, this),
        CC_CALLBACK_1(OpenScene::menuCloseCallback, this)
    };
    
	for (int i = 0; i < 5; ++i) {
		auto menuI = cocos2d::MenuItemImage::create(UiNames[i] + ".png", UiNames[i] + "Selected.png", Uifuncs[i]);
		if (i != 0)
			menuI->setScale(0.8, 0.6);
		vecs.pushBack(menuI);
	}

	UImenus = cocos2d::Menu::createWithArray(vecs);
	UImenus->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	UImenus->alignItemsVertically();
	return UImenus;
}


void OpenScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


void OpenScene::SwitchToOpen(cocos2d::Ref *pSender) {
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
	audio->playBackgroundMusic("music/Temple of Time.mp3");
	auto dir = cocos2d::Director::getInstance();
	dir->replaceScene(HelloWorld::createScene());
}

void OpenScene::GameSetting(cocos2d::Ref* pSender) {
	Director::getInstance()->pushScene(Settings::createScene());
}

void OpenScene::OnTouchPause(cocos2d::Ref* pSender) {
	auto layer = PauseWithLabelLayer::create();

	static std::string helps[] = { "Hi, this is a bnb game", "made by maplewind, Chris and shadowfox",
		"use up\\down\\left\\right to control your charactor",
		"and you can press \"help\" to get some information",
		"have fun~" };

	for (int i = 0; i < 5; ++i) {
		auto label = MenuItemLabel::create(Label::create(helps[i], "fonts/GloriaHallelujah.ttf", 35));
		label->setColor(Color3B::BLACK);
		layer->_menuitems.pushBack(label);
	}
	auto show_menus = Menu::createWithArray(layer->_menuitems);
	show_menus->alignItemsVertically();
	layer->addChild(show_menus);
	layer->_parent = this;

	//    this->UImenus->setEnabled(false);

	//    layer->create_func = create;    //  保存函数

	addChild(layer, 100);
}

void OpenScene::OnTouchResume() {
	UImenus->setEnabled(true);
}


void OpenScene::ToStartInGame(Ref *sender) {
	Director::getInstance()->replaceScene(RoomChoose::createScene());
}

void OpenScene::ToLogIn(cocos2d::Ref* sender) {
    Director::getInstance()->replaceScene(LoginScene::createScene());
}
