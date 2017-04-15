#include "OpenScene.h"

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
    
    auto backGround = cocos2d::Sprite::create("BackGround/temple of times.png");
    backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height /2));
    this->addChild(backGround, 0);
    
    
    auto menu_list = setLayOutL1();
    addChild(menu_list);
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("music/When The Morning Comes.mp3", true);
    auto musicList = cocos2d::MenuItemToggle::createWithCallback(CC_CALLBACK_1(OpenScene::musicOnAndOff, this), cocos2d::MenuItemFont::create("Music On"),   cocos2d::MenuItemFont::create("Music Off"), nullptr);
    auto musicM = cocos2d::Menu::create(musicList, nullptr);
    
//    absolutelyLayoutScrollView();
    
    addChild(musicM);
    musicM->setPosition(cocos2d::Vec2(visibleSize.width-60, 20));
    
    absolutelyLayoutListView();
    
    return true;
}

cocos2d::Menu* OpenScene::setLayOutL1() {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    const std::string label_names[] = {"Play On Internet", "Play Myself", "Quit"};
    cocos2d::Vector<cocos2d::MenuItem*> vecs;
    
    vecs.pushBack(cocos2d::MenuItemLabel::create(Label::create("FinalProject", "Arial.ttf", 50)));
    
    for (int i = 0; i < 1; ++i)
        vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create(label_names[i], "fonts/Marker Felt.ttf", 30)));
    vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create("Play Myself", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenScene::SwitchToOpen, this)));
    vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create("Help", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_0(OpenScene::absolutelyLayoutScrollView, this)));
    vecs.pushBack(cocos2d::MenuItemLabel::create(cocos2d::Label::create("Settings", "fonts/Marker Felt.ttf", 30)));
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
    dir->replaceScene(HelloWorld::createScene());
}

//void OpenScene::absolutelyLayoutScrollView() {
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    
//    Size scollFrameSize = Size(visibleSize.width - 30.f, visibleSize.height - 10.f);
//    auto scrollView = cocos2d::ui::ScrollView::create();
//    scrollView->setBackGroundColorType(cocos2d::ui::LAYOUT_COLOR_SOLID);
//    scrollView->setBackGroundColor(Color3B(200, 200, 200));
//    scrollView->setSize(scollFrameSize);
//    scrollView->setPosition(Point(15, 5));
//    scrollView->setDirection(cocos2d::ui::SCROLLVIEW_DIR_VERTICAL);
//    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height * 2);
//    scrollView->setInnerContainerSize(containerSize);
//    
//    auto textWidget = Label::create("xxd", "fonts/Marker Felt.ttf", 30);;
//    textWidget->setPosition(Point(containerSize.width / 2, containerSize.height / 2));
//    scrollView->addChild(textWidget);
//    
//    auto buttonWidget = cocos2d::ui::Button::create("CloseSelected.png", "CloseNormal.png");
//    buttonWidget->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
//        
//    });
//    buttonWidget->setPosition(Point(containerSize.width / 2, containerSize.height / 2 - 100));
//    scrollView->addChild(buttonWidget);
//    
//    addChild(scrollView);
//}
//
//cocos2d::ui::ListView* OpenScene::absolutelyLayoutListView() {
//    using namespace cocos2d;
//    auto vis = Director::getInstance()->getVisibleSize();
//    auto lv = cocos2d::ui::ListView::create();
//    lv->setDirection(cocos2d::ui::SCROLLVIEW_DIR_VERTICAL);
//    lv->setTouchEnabled(true);
//    lv->setBounceEnabled(true);
//    lv->setBackGroundColor(Color3B::BLACK);
//    lv->setContentSize(Size(240, 130));
//    lv->setPosition(vis / 2);
//    lv->addChild(Label::create("hello", "fonts/Marker Felt.ttf", 30));
//    lv->setPosition(Vec2(200, 200));
//    this->addChild(lv);
//    return lv;
//}
