#include "settingScene.h"
#include "OpenScene.h"
#include "SimpleAudioEngine.h"
/*�����setting ������
1.��Ч���� ����Ч���ڴ�С��
2.���ֿ��� �����ֵ��ڴ�С��
3.��Ϸ�������ã�ʲô�������ƶ���ʲô���������ڣ�
4.��Ϸ�Ľ��ȣ��� ���� ����

�Ѷȵ�ѡ����������ѡ���Լ��ؿ���ѡ�����������ѡ�� ���� GameScene ����
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
		nullptr
	);

	soundToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3)));
	
		//���ֲ���
	auto labelSound = Label::createWithTTF("Sound", "fonts/arial.ttf",24);
	labelSound->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3)));
	this->addChild(labelSound);


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
		nullptr
	);

	musicToggleMenuItem->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 3 + 100)));

		//���ֲ���
	auto labelMusic = Label::createWithTTF("Music", "fonts/arial.ttf", 24);
	labelMusic->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelMusic);

	//��Ϸ��������  ��֪����ôŪ�ȿ���

	//��Ϸ���ȿ���   ����ʱ�����ִ��棩
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
		//������ʾ
	auto labelSchedule = Label::createWithTTF("Schedule", "fonts/arial.ttf", 24);
	labelSchedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 380,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelSchedule);

	//Ok��ť �� ���ص������� 
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


/******��ʵ�ֵĿ��ز���******/
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