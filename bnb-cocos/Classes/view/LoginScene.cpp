#include "LoginScene.h"
#include "TextField.h"
#include "ui/CocosGUI.h"
#include "RoomChooseScene.h"
<<<<<<< HEAD
=======
#include <fstream>
>>>>>>> WebGameLogic

USING_NS_CC;

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    using namespace ui;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
<<<<<<< HEAD
=======

>>>>>>> WebGameLogic
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto backGround = cocos2d::Sprite::create("BackGround/Gray World.jpg");
    backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround, 0);
    
<<<<<<< HEAD
    
    
=======
>>>>>>> WebGameLogic
    auto field = TextFieldTest::create();
    field->setPosition(visibleSize.height * 0.15, visibleSize.height* 0.25);
    addChild(field);
    
    auto return_button = Button::create("GameUI/GetStart.png");
    return_button->setPosition(Vec2(visibleSize.width / 2, 100));
    return_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 没有输入提醒重新输入
            if (field->unInputData()) {
                field->showDidNotInput();
                return;
            }
            // 设置玩家自己的名称
            log("%s", field->showInputData().c_str());
<<<<<<< HEAD
=======
			std::fstream outfile("e:\\name.txt");
			if (!outfile.is_open())
			{
				return;
			}
			outfile << field->showInputData() << "\n";
>>>>>>> WebGameLogic
            UserDefault::getInstance()->setStringForKey("MyName", field->showInputData());
            // 切换到Room Choose场景
            auto transition = TransitionShrinkGrow::create(2.0, RoomChoose::createScene());
            Director::getInstance()->replaceScene(transition);
<<<<<<< HEAD
=======
			outfile.close();
>>>>>>> WebGameLogic
        }
    });
    addChild(return_button);
    
    return true;
}

