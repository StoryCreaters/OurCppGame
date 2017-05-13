#include "settingScene.h"
#include "SimpleAudioEngine.h"

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

	//��Ч����   ֻ�и���ʽ�ϵĿ��ء���ɶҲ���ܸɵģ���Ҫ����
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
		NULL
	);

	soundToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3)));

	//���ֿ���   ͬ�ϣ�ֻ�и���ʽ�ϵĿ��ء���ɶҲ���ܸɵģ���Ҫ����
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
		NULL
	);

	musicToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 100)));

	//Ok��ť �� ���ص������� 
	auto okMenuItem = MenuItemImage::create(
		"SettingScene/OK1.png",
		"SettingScene/OK2.png",
		CC_CALLBACK_1(Setting::menuOkCallback, this)
	);
	okMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 200)));

	Menu *mn = Menu::create(soundToggleMenuItem,
		musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void Setting::menuOkCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}


/******��ʵ�ֵĿ��ز���******/
void Setting::menuSoundToggleCallback(cocos2d::Ref* pSender)
{

}

void Setting::menuMusicToggleCallback(cocos2d::Ref* pSender)
{

}