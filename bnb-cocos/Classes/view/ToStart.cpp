#include "ToStart.h"

USING_NS_CC;

Scene* ToStart::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ToStart::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool ToStart::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backGround = Sprite::create("BackGround/grunge-background.jpg");
    backGround->setPosition(visibleSize / 2);
    backGround->setScale(0.7f);
    addChild(backGround);
    
    return true;
}
