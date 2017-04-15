#include "OpenScene.h"


void OpenScene::musicOnAndOff(cocos2d::Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    static int times = 0;
    if (times++ % 2 == 0) {
        audio->pauseBackgroundMusic();
    }
    else
        audio->resumeBackgroundMusic();
}

// on "init" you need to initialize your instance
bool OpenScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    auto backGround = cocos2d::Sprite::create("BackGround/TOT.png");
    backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height /2));
    this->addChild(backGround, 0);
    
    
    auto menu_list = setLayOutL1();
    addChild(menu_list);
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("music/When The Morning Comes.mp3", true);
    auto musicList = cocos2d::MenuItemToggle::createWithCallback(CC_CALLBACK_1(OpenScene::musicOnAndOff, this), cocos2d::MenuItemFont::create("Music On"),   cocos2d::MenuItemFont::create("Music Off"), nullptr);
    auto musicM = cocos2d::Menu::create(musicList, nullptr);
    
    addChild(musicM);
    musicM->setPosition(cocos2d::Vec2(visibleSize.width-60, 20));
    
    return true;
}

cocos2d::Menu* OpenScene::setLayOutL1() {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    const std::string label_names[] = {"Play On Internet", "Play Myself", "Quit"};
    cocos2d::Vector<cocos2d::MenuItem*> vecs;
    for (int i = 0; i < 2; ++i)
        vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create(label_names[i], "fonts/Marker Felt.ttf", 30)));
    
    
    vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create("newGameHere", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenScene::SwitchToOpen, this)));
    vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create(label_names[2], "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenScene::menuCloseCallback, this)));
    
    auto menu_list = cocos2d::Menu::createWithArray(vecs);
    menu_list->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    menu_list->alignItemsVertically();
    return menu_list;
}



//cocos2d::Menu* HelloWorld::setMusicLine(const std::string &music_name) {
//    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
//    audio->playBackgroundMusic(music_name.c_str(), true);
//    auto musicList = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::musicOnAndOff, this), MenuItemFont::create("Music On"),   MenuItemFont::create("Music Off"), nullptr);
//    auto musicM = Menu::create(musicList, nullptr);
//    return musicM;
////}

void OpenScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    cocos2d::Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void OpenScene::SwitchToOpen(cocos2d::Ref *pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("music/Temple of Time.mp3");
    auto dir = cocos2d::Director::getInstance();
    dir->replaceScene(OpenScene::createScene());
}

