#include "PropLayer.h"
#include "GameItem.h"
#include "Settings.h"
#include "GameScene.h"
#include "WebClient.h"

using namespace ui;
using namespace std;
// find out the rule of lambda
Layer* PropLayer::getPropLayer() {
    return dynamic_cast<Layer*>(GameScene::getCurrentMap()->getChildByName("PropLayer"));
}
constexpr char* res[] = {
    "Gift_RspeedUp",
    "Gift_needle",
    "Gift_guard",
    "Gift_upper"
};

std::function<void()> PropLayer::getPropfuncs(int index) {
    // TODO: 用std::bind优化
    switch (index) {
        case 0:
            return [](){return character::getMychara()->rideSpeedUp();};
            break;
        case 1:
            return [](){return character::getMychara()->UseNeedle();};
            break;
        case 2:
            return [](){return character::getMychara()->setGuard();};
            break;
        case 3:
            return [](){return character::getMychara()->powerup();};
            break;
    }
}

std::function<bool()> PropLayer::getAblefuncs(int index) {
    switch (index) {
        case 0:
            return [](){return character::getMychara()->isRiding();};
            break;
        case 1:
            return [](){return character::getMychara()->isStucked();};
            break;
        case 2:
            return [](){return true;};
            break;
        case 3:
            return [](){return true;};
            break;
    }
}

std::function<void(character* chara)> PropLayer::getOtherPropfuncs(int index) {
    switch (index) {
        case 0:
            return [](character* charac){return charac->rideSpeedUp();};
            break;
        case 1:
            return [](character* charac){return charac->UseNeedle();};
            break;
        case 2:
            return [](character* charac){return charac->setGuard();};
            break;
        case 3:
            return [](character* charac){return charac->powerup();};
            break;
    }
}

bool PropLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    for (int i = 0; i < prop_nums; ++i) {
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
        label = LabelTTF::create("0", "Marker Felt", 32);
        label->setPosition(cocos2d::Vec2(x + buttonSize.width*0.15, y + buttonSize.height*0.85));
        label->setName("label");
        cur_button->addChild(label);
        cur_button->setTag(i);
//        log("index:%d, string: %s", i, res[i]);
        addChild(cur_button);
    }
//    propfuncs[PropLayer::prop_nums] = {std::bind(&character::powerup(),character::getMychara()), std::bind(&character::setGuard(),character::getMychara()),    std::bind(character::UseNeedle(), character::getMychara()), std::bind(, character::getMychara())};
    auto button0 = (Button*)this->getChildByTag(0);
    button0->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propMinus(0, this);
            
        }
    });
    auto button1 = (Button*)this->getChildByTag(1);
    button1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            propMinus(1, this);
            
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
//    log("prop~~~~~~~~~~~~~~");
    return true;
}
//改变道具数量的函数
void PropLayer::propPlus(int i, Ref *sender)
{
    addProp(i);
}

void PropLayer::propMinus(int i, Ref *sender) {
    useProp(i);
}

void PropLayer::addProp(int index) {
//    log("index %d", index);
    ++currentProps[index];
    auto button = this->getChildByTag(index);
    auto scorelabel = (LabelTTF*)(button->getChildByName("label"));
    auto s = scorelabel->getString();
    int num = atoi(s.c_str());
//    log("num=%d", num);
    auto width = scorelabel->getPosition().x;
    auto height = scorelabel->getPosition().y;
    button->removeChildByName("label");
    string s2;
    s2 = to_string(num + 1);
    LabelTTF* label = LabelTTF::create(s2, "Marker Felt", 32);
    label->setPosition(cocos2d::Vec2(width, height));
    label->setName("label");
    button->addChild(label);
    
}

void PropLayer::useProp(int index) {
    if (!getAblefuncs(index)()) {
        return;
    }
    auto button = this->getChildByTag(index);
    auto scorelabel = (LabelTTF*)(button->getChildByName("label"));
    auto s = scorelabel->getString();
    int num = atoi(s.c_str());
    if (num >= 1) {
        --currentProps[index];
        auto width = scorelabel->getPosition().x;
        auto height = scorelabel->getPosition().y;
        button->removeChildByName("label");
        string s2;
        s2 = to_string(num - 1);
        LabelTTF* label = LabelTTF::create(s2, "Marker Felt", 32);
        label->setPosition(cocos2d::Vec2(width, height));
        label->setName("label");
        button->addChild(label);
        getPropfuncs(index)();
        // 本玩家使用index号道具
        WebClient::getInstance()->send_data("use " + std::to_string(index));
    }
}

void PropLayer::useRecv(int index, character* chara) {
    getOtherPropfuncs(index)(chara);
}
