#include "OpenScene.h"
#include "PauseWithLabelLayer.h"
#include "ToStart.h"
#include "GameScene.h"
// TEST
#include "PreLoadScene.h"

Scene* OpenScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OpenScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

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
    
    auto backGround = cocos2d::Sprite::create("BackGround/Gray World.jpg");
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
    
    cocos2d::Vector<cocos2d::MenuItem*> vecs;
    
    std::string UiNames[] = {"GameUI/ProjectName", "GameUI/PlayMyself", "GameUI/PlayOnInternet", "GameUI/Help","GameUI/Quit"};
    ccMenuCallback Uifuncs[] = {nullptr,CC_CALLBACK_1(OpenScene::sceneTest, this), nullptr,CC_CALLBACK_1(OpenScene::OnTouchPause, this),CC_CALLBACK_1(OpenScene::menuCloseCallback, this)};
    for (int i = 0; i < 5; ++i) {
        auto menuI = cocos2d::MenuItemImage::create(UiNames[i] + ".png", UiNames[i]+ "Selected.png",Uifuncs[i]);
        if (i != 0)
            menuI->setScale(0.8, 0.6);
        vecs.pushBack(menuI);
    }
    
    UImenus = cocos2d::Menu::createWithArray(vecs);
    UImenus->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    UImenus->alignItemsVertically();
    return UImenus;
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
    dir->replaceScene(HelloWorld::createScene());
}


void OpenScene::OnTouchPause(cocos2d::Ref* pSender) {
    auto layer = PauseWithLabelLayer::create();
    
    static std::string helps[] = {"Hi, this is a bnb game", "made by maplewind, Chris and shadowfox",
        "use up\\down\\left\\right to control your charactor",
        "and you can press \"help\" to get some information",
        "have fun~"};
    
    for (int i = 0; i < 5; ++i) {
        auto label = MenuItemLabel::create(Label::create(helps[i], "fonts/GloriaHallelujah.ttf", 35));
        label->setColor(Color3B::BLACK);
        layer->_menuitems.pushBack(label);
    }
    auto show_menus = Menu::createWithArray(layer->_menuitems);
    show_menus->alignItemsVertically();
    layer->addChild(show_menus);
    layer->_parent = this;
    
//    this->UImenus->setEnabled(false);
    
//    layer->create_func = create;    //  保存函数
    
    addChild(layer, 100);
}

void OpenScene::OnTouchResume() {
    UImenus->setEnabled(true);
}

void OpenScene::ToStartGame(Ref *sender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("music/Exit Music.mp3");
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void OpenScene::sceneTest(Ref *sender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    Director::getInstance()->replaceScene(PreLoadScene::createScene());
}
