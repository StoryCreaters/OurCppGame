#include "RoomChooseScene.h"
#include "Character.h"
#include "GameScene.h"
#include "CharacterSelect.h"

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/Gray World.jpg");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	cocos2d::Vector<cocos2d::MenuItem*> vecs;

	std::string UiNames[] = { "GameUI/RoomChoose", "GameUI/Room1", "GameUI/Room2", "GameUI/Room3","GameUI/Room4"};
	ccMenuCallback Uifuncs[] = { nullptr,CC_CALLBACK_1(RoomChoose::ToRoomOne, this), CC_CALLBACK_1(RoomChoose::ToRoomTwo, this),CC_CALLBACK_1(RoomChoose::ToRoomThree, this),CC_CALLBACK_1(RoomChoose::ToRoomFour, this) };
	for (int i = 0; i < 5; ++i) {
		auto menuI = cocos2d::MenuItemImage::create(UiNames[i] + ".png", UiNames[i] + "Selected.png", Uifuncs[i]);
		if (i != 0)
			menuI->setScale(0.8, 0.6);
		vecs.pushBack(menuI);
	}

	UImenus = cocos2d::Menu::createWithArray(vecs);
	UImenus->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	UImenus->alignItemsVertically();
	addChild(UImenus);

	return true;
}

void RoomChoose::ToRoomOne(Ref *sender) {
	UserDefault::getInstance()->setIntegerForKey("Room", 1);
	Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomTwo(Ref *sender) {
	UserDefault::getInstance()->setIntegerForKey("Room", 2);
	Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomThree(Ref *sender) {
	UserDefault::getInstance()->setIntegerForKey("Room", 3);
	Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomFour(Ref *sender) {
	UserDefault::getInstance()->setIntegerForKey("Room", 4);
	Director::getInstance()->replaceScene(Players::createScene());
}