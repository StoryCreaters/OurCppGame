#include "PropLayer.h"
#include "GameItem.h"
#include "Settings.h"

constexpr char* res[] = {
    "Gift_RspeedUp",
    "Gift_needle",
    "Gift_guard",
    "Gift_upper"
};

bool PropLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    for (int i = 0; i < prop_nums; ++i) {
        auto cur_button = cocos2d::ui::Button::create(settings::PropLayer::gridBkg);
        cur_button->addChild(Sprite::createWithSpriteFrameName(std::string(res[i]) + "_01.png"));
        addChild(cur_button);
    }
    return true;
}
