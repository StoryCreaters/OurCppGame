#include "settingScene.h"
#include "OpenScene.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
/*�����GameSettings ������
1.��Ч���� ����Ч���ڴ�С��
2.���ֿ��� �����ֵ��ڴ�С��
3.��Ϸ�������ã�ʲô�������ƶ���ʲô���������ڣ�
4.��Ϸ�Ľ��ȣ��� ���� ����

�Ѷȵ�ѡ����������ѡ���Լ��ؿ���ѡ�����������ѡ�� ���� GameScene ����
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


	//��Ч����  
	/*
	TODO:ʵ�ֵ������ܹ�ͣ��Ч��������һ�������������ڣ�
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
	
		//���ֲ���
	auto labelSound = Label::createWithTTF("Sound", "fonts/GloriaHallelujah.ttf",24);
	labelSound->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3)));
	this->addChild(labelSound);


	//���ֿ���  
	/*
	TODO:ʵ�ֵ������ܹ�ͣ��Ч��������һ�������������ڣ�
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

		//���ֲ���
	auto labelMusic = Label::createWithTTF("Music", "fonts/GloriaHallelujah.ttf", 24);
	labelMusic->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelMusic);

	//���Ƽ�������  ����ȱ��
	/*
	TODO:
	  1.��ɫ��������
	  2.�����ݼ�
	*/

	//��Ϸ���ȿ���   
	/*
	TODO:
	�򵥵�˵������Ϸ���ٶȿ������ߵÿ죬�ߵ���������ͨ��������ڡ�
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
		//������ʾ
	auto labelSchedule = Label::createWithTTF("Schedule", "fonts/GloriaHallelujah.ttf", 24);
	labelSchedule->setPosition(Director::getInstance()->
		convertToGL(Vec2(origin.x + visibleSize.width / 2 - 380,
			origin.y + visibleSize.height / 3 + 100)));
	this->addChild(labelSchedule);

	//Ok��ť �� ���ص������� 
	/*
	���ͣ��ص�������
	BUG:�������ֻ����²���
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

/******��ʵ�ֵĿ��ز���******/
void GameSettings::menuSoundToggleCallback(cocos2d::Ref* pSender)
{

}

void GameSettings::menuMusicToggleCallback(cocos2d::Ref* pSender)
{

}

