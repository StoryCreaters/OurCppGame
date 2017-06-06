﻿#include "PropLayer.h"
#include "GameItem.h"
#include "Settings.h"
#include "GameScene.h"
using namespace ui;
using namespace std;
Layer* PropLayer::getPropLayer() {
    return dynamic_cast<Layer*>(GameScene::getCurrentMap()->getChildByName("PropLayer"));
}
constexpr char* res[] = {
    "Gift_RspeedUp",
    "Gift_needle",
    "Gift_guard",
    "Gift_upper"
};
int i;
bool PropLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    for (i = 0; i < prop_nums; ++i) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        auto cur_button = Button::create(settings::PropLayer::gridBkg);
        Size buttonSize = cur_button->getContentSize();
        cur_button->setPosition(cocos2d::Vec2(visibleSize.width *0.1, visibleSize.height *0.2 + i*buttonSize.height));
        CCPoint objpoint = getPosition();
        float x = objpoint.x;
        float y = objpoint.y;
        auto propitems = Sprite::createWithSpriteFrameName(std::string(res[i]) + "_01.png");
        propitems->setPosition(Vec2(x + buttonSize.width*0.5, y + buttonSize.height*0.5));
        cur_button->addChild(propitems, 0);
        LabelTTF* label;
        label = LabelTTF::create("1", "Marker Felt", 32);
        label->setPosition(cocos2d::Vec2(x + buttonSize.width*0.15, y + buttonSize.height*0.85));
        cur_button->addChild(label, 3, i);
        addChild(cur_button, 1, i);
    }
    auto button0 = (Button*)this->getChildByTag(0);
    button0->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propPlus(0, this);
            
        }
    });
    auto button1 = (Button*)this->getChildByTag(1);
    button1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propPlus(1, this);
            
        }
    });
    auto button2 = (Button*)this->getChildByTag(2);
    button2->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propMinus(2, this);
            
        }
    });
    auto button3 = (Button*)this->getChildByTag(3);
    button3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propMinus(3, this);
            
        }
    });
    log("prop~~~~~~~~~~~~~~");
    return true;
}
//改变道具数量的函数
void PropLayer::propPlus(int i, Ref *sender)
{
    auto button=(Button*)this->getChildByTag(i);
    auto scorelabel = (LabelTTF*)button->getChildByTag(i);
    auto s = scorelabel->getString();
    int num = atoi(s.c_str());
    log("num=%d", num);
    if (num >= 1) {
        auto width = scorelabel->getPosition().x;
        auto height = scorelabel->getPosition().y;
        button->removeChildByTag(i);
        string s2;
        s2 = to_string(num - 1);
        LabelTTF* label = LabelTTF::create(s2, "Marker Felt", 32);
        label->setPosition(cocos2d::Vec2(width, height));
        button->addChild(label, 1, i);
    }
}

void PropLayer::propMinus(int i, Ref *sender) {
    auto button = (Button*)this->getChildByTag(i);
    auto scorelabel = (LabelTTF*)button->getChildByTag(i);
    auto s = scorelabel->getString();
    int num = atoi(s.c_str());
    log("num=%d", num);
    auto width = scorelabel->getPosition().x;
    auto height = scorelabel->getPosition().y;
    button->removeChildByTag(i);
    string s2;
    s2 = to_string(num + 1);
    LabelTTF* label = LabelTTF::create(s2, "Marker Felt", 32);
    label->setPosition(cocos2d::Vec2(width, height));
    button->addChild(label, 1, i);
}
