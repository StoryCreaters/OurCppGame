#include "BaseController.h"

using namespace cocos2d;

bool BaseController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // add listenner
    initListenner();
    
    
    return true;
}

void BaseController::initListenner() {
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BaseController::myKeyboardPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(BaseController::myKeyboardOff, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseController::ControllerSetEnabled() {
    this->_eventDispatcher->setEnabled(false);
}
void BaseController::ControllerSetAbled() {
    this->_eventDispatcher->setEnabled(true);
}
