// 理想状况这里应该用继承的... 但是这里先写一个试试看咯～
#include "GameScene.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    addCloseMenu();
    
    // 一张临时背景
    auto backG = Sprite::create("BackGround/Cool_background.jpg");
    addChild(backG, -10);
    backG->setPosition(visibleSize / 2);
    
    // tile map and basic player
    _tileMap = TMXTiledMap::create("gameStart/map01.tmx");
    _background = _tileMap->layerNamed("Background");
    
    _tileMap->setAnchorPoint(Vec2(0.5f, 0.5f));
    _tileMap->setPosition(Point(visibleSize.width / 2 , visibleSize.height / 2));
    _tileMap->setScale(1.15f);
    
    // 注意坐标位置差
    auto offx = (visibleSize.width - _tileMap->getContentSize().width)/ 2;
    auto offy = (visibleSize.height - _tileMap->getContentSize().height) / 2;
    TMXObjectGroup *objects = _tileMap->getObjectGroup("player");
    CCASSERT(nullptr != objects, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint1");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    int x = spawnPoint["x"].asFloat();
    int y = spawnPoint["y"].asFloat();
    // 用某个该死的家伙建立精灵
    
    _myplayer = character::create(character::MAPLE_WISH);
    _myplayer->setPosition(offx + x, offy + y);
    
    addChild(_myplayer);
    addChild(_tileMap, -1);

    // 键盘监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::myKeyboardOnL, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::myKeyboardOffL, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void GameScene::setViewPointCenter(Point position) {
    auto winSize = Director::getInstance()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);
    
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void GameScene::addCloseMenu() {
    // close menu
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto closeMenu = Menu::create(closeItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);
}

void GameScene::myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    GameScene::_optionCode code;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            code = _optionCode::GO_UP;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            code = _optionCode::GO_DOWN;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            code = _optionCode::GO_LEFT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            code = _optionCode::GO_RIGHT;
            break;
        default:
            break;
    }
    // DEBUG
//    log("hei jilao");
    _my_sprite_move[code] = true;       //有移动的趋势
}

void GameScene::mySpriteMove() {
    Vector<FiniteTimeAction *> moves;
    const int step = 5;
    float dur = 0.1f;
    //TODO:增加边界检测
    // 获得x y 的上界 下界
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto offx = (visibleSize.width - _tileMap->getContentSize().width)/ 2;
    auto offy = (visibleSize.height - _tileMap->getContentSize().height) / 2;
    auto lowerx = offx, upperx = visibleSize.width - offx;
    auto lowery = offy, uppery = visibleSize.height - offy;
    
    const static int BORDER = 2;        //边界长
    
    if (_my_sprite_move[GO_RIGHT]) {
//        moves.pushBack(MoveBy::create(dur, Vec2(step, 0)));
        if (upperx >= _myplayer->getPosition().x + BORDER)
            moves.pushBack(MoveBy::create(dur, Vec2(step, 0)));
    }
    
    if (_my_sprite_move[GO_LEFT]) {
//        moves.pushBack(MoveBy::create(dur, Vec2(-step, 0)));
        if (lowerx <= _myplayer->getPosition().x - BORDER)
            moves.pushBack(MoveBy::create(dur, Vec2(-step, 0)));
    }
    
    if (_my_sprite_move[GO_UP]) {
//        moves.pushBack(MoveBy::create(dur, Vec2(0, step)));
        if (uppery >= _myplayer->getPosition().y + BORDER)
            moves.pushBack(MoveBy::create(dur, Vec2(0, step)));
    }
    
    if (_my_sprite_move[GO_DOWN]) {
//        moves.pushBack(MoveBy::create(dur, Vec2(0, -step)));
        if (lowery <= _myplayer->getPosition().y - BORDER)
            moves.pushBack(MoveBy::create(dur, Vec2(0, -step)));
    }
    
    // 有可能啥都没有2333
    if (moves.size())
        _myplayer->runAction(cocos2d::Spawn::create(moves));
}

void GameScene::myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    GameScene::_optionCode code;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            code = _optionCode::GO_UP;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            code = _optionCode::GO_DOWN;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            code = _optionCode::GO_LEFT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            code = _optionCode::GO_RIGHT;
            break;
        default:
            break;
    }
    // DEBUG
    //    log("hei jilao");
    _my_sprite_move[code] = false;       //有移动的趋势
}

void GameScene::update(float dt) {
    mySpriteMove();
}
