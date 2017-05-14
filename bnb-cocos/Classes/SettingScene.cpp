#include "settingScene.h"
#include "OpenScene.h"
#include "SimpleAudioEngine.h"
/*理想的setting 包括：
1.音效开关 （音效调节大小）
2.音乐开关 （音乐调节大小）
3.游戏键的设置（什么键用来移动，什么键用来放炮）
4.游戏的进度（快 正常 慢）

难度的选择还有人数的选择以及关卡的选择（甚至人物的选择） 留在 GameScene 界面
*/
USING_NS_CC;

Scene* Setting::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Setting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Setting::init()
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


	//音效开关   只有个形式上的开关……啥也不能干的，需要完善
	auto soundOnMenuItem = MenuItemImage::create(
		"SettingScene/on.png",
		"SettingScene/on.png"
	);
	auto soundOffMenuItem = MenuItemImage::create(
		"SettingScene/off.png",
		"SettingScene/off,png"
	);

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		nullptr
	);

	soundToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3)));
	
		//文字部分
	auto labelSound = Label::createWithTTF("Sound", "fonts/arial.ttf",24);
	labelSound->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3)));
	this->addChild(labelSound);


	//音乐开关   同上，只有个形式上的开关……啥也不能干的，需要完善
	auto musicOnMenuItem = MenuItemImage::create(
		"SettingScene/on.png",
		"SettingScene/on.png"
	);
	auto musicOffMenuItem = MenuItemImage::create(
		"SettingScene/off.png",
		"SettingScene/off.png"
	);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		nullptr
	);

	musicToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 100)));

		//文字部分
	auto labelMusic = Label::createWithTTF("Music", "fonts/arial.ttf", 24);
	labelMusic->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelMusic);

	//游戏键的设置  不知道怎么弄先空着

	//游戏进度快慢   （临时用文字代替）
	MenuItemFont * quickItem = MenuItemFont::create("Quick",
		CC_CALLBACK_1(Setting::menuQuickItemCallback, this));
	MenuItemFont * normalItem = MenuItemFont::create("Normal",
		CC_CALLBACK_1(Setting::menuNormalItemCallback, this));
	MenuItemFont * slowItem = MenuItemFont::create("Slow",
		CC_CALLBACK_1(Setting::menuSlowItemCallback, this));
	Menu * schedule = Menu::create(quickItem, normalItem,
		slowItem, nullptr);
	schedule->alignItemsVertically();
	schedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 250,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(schedule,0);
		//文字提示
	auto labelSchedule = Label::createWithTTF("Schedule", "fonts/arial.ttf", 24);
	labelSchedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 380,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelSchedule);

	//Ok按钮 ， 返回到主界面 
	auto okMenuItem = MenuItemImage::create(
		"SettingScene/OK1.png",
		"SettingScene/OK2.png",
		CC_CALLBACK_1(Setting::menuOkCallback, this)
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

void Setting::menuOkCallback(cocos2d::Ref* pSender)
{
	auto sc = OpenScene::createScene();
	auto reScene = TransitionSlideInL::create(0.618f, sc);
	Director::getInstance()->replaceScene(reScene);
}


/******待实现的开关部分******/
void Setting::menuSoundToggleCallback(cocos2d::Ref* pSender)
{

}

void Setting::menuMusicToggleCallback(cocos2d::Ref* pSender)
{

}

void Setting::menuQuickItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}

void Setting::menuNormalItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}

void Setting::menuSlowItemCallback(cocos2d::Ref* pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch Start Menu Item %p", item);
}