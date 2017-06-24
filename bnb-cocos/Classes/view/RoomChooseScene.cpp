#include "RoomChooseScene.h"
#include "Character.h"
#include "GameScene.h"
#include "CharacterSelect.h"
#include "OpenScene.h"
#include "WebClient.h"
#include "SceneManager.h"
#include "DataManager.h"

#define NUM 4;
USING_NS_CC;
using namespace ui;

Scene* RoomChoose::createScene() {
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();
	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = RoomChoose::create();
    layer->setName("RoomChoose");
    
    // 登陆进了roomselect
    WebClient::getInstance()->send_data("in");
	// 将GameSet层作为子节点添加到场景
	scene->addChild(layer);
	// 返回场景对象
	return scene;
}

RoomChoose* RoomChoose::getRoomChooseScene() {
    auto layer = Director::getInstance()->getRunningScene()->getChildByName("RoomChoose");
    auto tlayer = dynamic_cast<RoomChoose*>(layer);
    assert(tlayer);
    return tlayer;
}

bool RoomChoose::init() {
	// 调用父类的init方法
	if (!Layer::init()) {
		return false;
	}
	// 获得设备可见视图大小
	vecs = { 0 };
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/chooseroom.png");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	cocos2d::Vector<cocos2d::MenuItem*> vecs;
	std::string UiNames[] = { "GameUI/RoomChoose", "GameUI/Room1", "GameUI/Room2", "GameUI/Room3","GameUI/Room4" };
	ccMenuCallback Uifuncs[] = { nullptr,CC_CALLBACK_1(RoomChoose::ToRoomOne, this), CC_CALLBACK_1(RoomChoose::ToRoomTwo, this),CC_CALLBACK_1(RoomChoose::ToRoomThree, this),CC_CALLBACK_1(RoomChoose::ToRoomFour, this) };
	for (int i = 0; i < 5; ++i) {
		auto menuI = cocos2d::MenuItemImage::create(UiNames[i] + ".png", UiNames[i] + "Selected.png", Uifuncs[i]);
		if (i != 0)
			menuI->setScale(0.8, 0.6);
		vecs.pushBack(menuI);
	}
	LabelTTF* label_1;
	label_1 = LabelTTF::create("Room Name:", "Arial", 32);
	label_1->setColor(Color3B::BLACK);
	label_1->setPosition(cocos2d::Vec2(visibleSize.width /2, visibleSize.height*0.73 ));
	this->addChild(label_1);
	//房间人数
	auto * label = LabelTTF::create("Current people online :", "Arial", 32);
	label->setColor(Color3B::BLACK);
	label->setPosition(cocos2d::Vec2(visibleSize.width *0.8, visibleSize.height*0.73));
	addChild(label);
	for (int i = 0; i < 4; i++) {
		LabelTTF* label;
		//把这里的Number实现成现有人数
		label = LabelTTF::create("","Arial", 32);
        label->setString("Number: " + std::to_string(0));
        room_digits.pushBack(label);
		label->setColor(Color3B::BLACK);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.8, visibleSize.height*0.62 - i * 115));
		this->addChild(label);
	}

	UImenus = cocos2d::Menu::createWithArray(vecs);
	UImenus->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	UImenus->alignItemsVertically();
	addChild(UImenus);
	//房间编号
	auto * label_2 = LabelTTF::create("Room Number:", "Arial", 32);
	label_2->setColor(Color3B::BLACK);
	label_2->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height*0.73));
	addChild(label_2);
	for (int i = 0; i < 4; i++) {
        LabelTTF* label;
		label = LabelTTF::create(std::to_string(i + 1), "Arial", 32);
		label->setColor(Color3B::BLACK);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height*0.62 - i * 115));
        
        this->addChild(label);
	}
	// 创建“返回“按钮，点击时调用returnToMenu函数
	auto return_button = Button::create("GameUI/b1.png");
	return_button->setPosition(Vec2(visibleSize.width *0.85, visibleSize.height*0.18));
	return_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 切换到MenuScene场景
//			auto transition = TransitionShrinkGrow::create(2.0, OpenScene::createScene());
            WebClient::getInstance()->send_data("tostart");
            SceneManager::toLoginScene();
		}
	});
	this->addChild(return_button);
	return true;
}


//void RoomChoose::addroom(Ref* sender) {
//	if (!vecs.empty()) {
//		vecs.push_back(1);
//		log("vecs[i]=%d", vecs.back());
//	}
//}
//void RoomChoose::poproom( Ref* sender) {
//	if (!vecs.empty()) {
//		vecs.back()--;
//	}
//	
//}
void RoomChoose::ToRoomOne(Ref *sender) {
    
    WebClient::getInstance()->send_data("0");
    DataManager::getInstance()->setStringForKey("map", "01");
//    Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomTwo(Ref *sender) {
	WebClient::getInstance()->send_data("1");
    DataManager::getInstance()->setStringForKey("map", "02");
//    Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomThree(Ref *sender) {
	WebClient::getInstance()->send_data("2");
    DataManager::getInstance()->setStringForKey("map", "03");
//    Director::getInstance()->replaceScene(Players::createScene());
}
void RoomChoose::ToRoomFour(Ref *sender) {
	WebClient::getInstance()->send_data("3");
    DataManager::getInstance()->setStringForKey("map", "01");
//    Director::getInstance()->replaceScene(Players::createScene());
}

void RoomChoose::changeRooms(int *array) {
    for (int i = 0; i < 4; ++i) {
        if (array[i] == 5) {
            room_digits.at(i)->setString("isplaying");
        } else {
            room_digits.at(i)->setString("numbers:" + std::to_string(array[i]));
        }
    }
}
