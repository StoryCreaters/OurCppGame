#include "PauseWithLabelLayer.h"
#include "SwallowTouch.h"

// 创建一个带string的层，用于pause，vector<string>的string,打印在屏幕上，并提供开始接口

cocos2d::Scene* PauseWithLabelLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseWithLabelLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool PauseWithLabelLayer::init()
{
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }
    
    this->initWithColor(cocos2d::Color4B(162, 162, 162, 128));
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    addUI();
    addChild(SwallowTouch::create());
    return true;
}


bool PauseWithLabelLayer::initialWithMenuVec(cocos2d::Vector<cocos2d::MenuItem*> &MenuToAdds) {
    this->_menuitems = MenuToAdds;
    return PauseWithLabelLayer::init();
}

void PauseWithLabelLayer::addUI() {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto close_menu = cocos2d::MenuItemLabel::create(cocos2d::Label::create("Back", "fonts/Marker Felt.ttf", 50), CC_CALLBACK_1(PauseWithLabelLayer::back, this));
    close_menu->setPosition(visibleSize.width / 2, visibleSize.height - 100);
    close_menu->setColor(cocos2d::Color3B::BLACK);
    this->_menuitems.pushBack(close_menu);
//    addChild(close_menu);
}

void PauseWithLabelLayer::back(cocos2d::Ref* obj)
{
    _eventDispatcher->removeEventListener(_listener);
    this->removeFromParentAndCleanup(true);
}
