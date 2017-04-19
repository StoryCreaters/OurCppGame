#include "SwallowTouch.h"
USING_NS_CC;
// 隔离层，别人写的
SwallowTouch::SwallowTouch(void)
{
}


SwallowTouch::~SwallowTouch(void)
{
}
bool SwallowTouch::init()
{
    if(!LayerColor::initWithColor(Color4B(100,100,100,50)))
        return false;
    auto visible = Director::getInstance()->getVisibleSize();
    
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = callback;
    
    listener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    
//    sMenu->setPosition(label->getPosition() - Point(0,100));
    
    return true;
}
void SwallowTouch::menuCallBack(cocos2d::Ref* sender)
{
    this->removeFromParentAndCleanup(true);
}
