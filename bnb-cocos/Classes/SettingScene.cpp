#include "settingScene.h"
#include "OpenScene.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
/*理想的GameSettings 包括：
1.音效开关 （音效调节大小）
2.音乐开关 （音乐调节大小）
3.游戏键的设置（什么键用来移动，什么键用来放炮）
4.游戏的进度（快 正常 慢）

难度的选择还有人数的选择以及关卡的选择（甚至人物的选择） 留在 GameScene 界面
*/
USING_NS_CC;

Scene* GameSettings::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSettings::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameSettings::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("BackGround/Gray World.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);


	//音效开关  
	/*
	TODO:实现点击后就能关停音效（或者用一个音量条来调节）
	*/
	auto soundOnMenuItem = MenuItemImage::create(
		"GameUI/on.png",
		"GameUI/on.png"
	);
	auto soundOffMenuItem = MenuItemImage::create(
		"GameUI/off.png",
		"GameUI/off,png"
	);

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(GameSettings::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		nullptr
	);

	soundToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3)));
	
		//文字部分
	auto labelSound = Label::createWithTTF("Sound", "fonts/GloriaHallelujah.ttf",24);
	labelSound->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3)));
	this->addChild(labelSound);


	//音乐开关  
	/*
	TODO:实现点击后就能关停音效（或者用一个音量条来调节）
	*/
	auto musicOnMenuItem = MenuItemImage::create(
		"GameUI/on.png",
		"GameUI/on.png"
	);
	auto musicOffMenuItem = MenuItemImage::create(
		"GameUI/off.png",
		"GameUI/off.png"
	);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(GameSettings::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		nullptr
	);

	musicToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 100)));

		//文字部分
	auto labelMusic = Label::createWithTTF("Music", "fonts/GloriaHallelujah.ttf", 24);
	labelMusic->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelMusic);

	//控制键的设置  （暂缺）
	/*
	TODO:
	  1.角色上下左右
	  2.放泡泡键
	*/

	//游戏进度快慢   
	/*
	TODO:
	简单地说就是游戏的速度快慢，走得快，走得慢，可以通过这里调节。
	*/
	MenuItemFont * quickItem = MenuItemFont::create("Quick",
		CC_CALLBACK_1(GameSettings::menuQuickItemCallback, this));
	MenuItemFont * normalItem = MenuItemFont::create("Normal",
		CC_CALLBACK_1(GameSettings::menuNormalItemCallback, this));
	MenuItemFont * slowItem = MenuItemFont::create("Slow",
		CC_CALLBACK_1(GameSettings::menuSlowItemCallback, this));
	Menu * schedule = Menu::create(quickItem, normalItem,
		slowItem, nullptr);
	schedule->alignItemsVertically();
	schedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 250,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(schedule,0);
		//文字提示
	auto labelSchedule = Label::createWithTTF("Schedule", "fonts/GloriaHallelujah.ttf", 24);
	labelSchedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 380,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelSchedule);

	//Ok按钮 ， 返回到主界面 
	/*
	解释：回到主界面
	BUG:背景音乐会重新播放
	*/
	auto okMenuItem = MenuItemImage::create(
		"GameUI/OK1.png",
		"GameUI/OK2.png",
		CC_CALLBACK_1(GameSettings::menuOkCallback, this)
	);
	okMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 400)));

	Menu *mn = Menu::create(soundToggleMenuItem,
		musicToggleMenuItem, okMenuItem, NULL);

	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void GameSettings::menuOkCallback(cocos2d::Ref* pSender)
{
	auto sc = OpenScene::createScene();
	auto reScene = TransitionSlideInL::create(0.618f, sc);
	Director::getInstance()->replaceScene(reScene);
}

void GameSettings::menuQuickItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}

void GameSettings::menuNormalItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}

void GameSettings::menuSlowItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}

/******待实现的开关部分******/
void GameSettings::menuSoundToggleCallback(cocos2d::Ref* pSender)
{

}

void GameSettings::menuMusicToggleCallback(cocos2d::Ref* pSender)
{

}

