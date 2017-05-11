// 理想状况这里应该用继承的... 但是这里先写一个试试看咯～
// TODO: 改变遮挡关系
// 泡泡炸裂
// 制作FSM
#include "GameScene.h"
#include "Bubbles.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace settings::GameScene;

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
    
//    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
//    audio->playBackgroundMusic(background_music, true);
//    audio->resumeAllEffects();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    addCloseMenu();
    
    // 一张临时背景
    auto backG = Sprite::create("BackGround/Cool_background.jpg");
    addChild(backG, -10);
    backG->setPosition(visibleSize / 2);
    
    /***** tilemap ******/
    _tileMap = TMXTiledMap::create("gameStart/map01.tmx");
    
    log("init:%f %f", _tileMap->getTileSize().height, _tileMap->getTileSize().width);
    
    _tileMap->setAnchorPoint(Vec2(0.5f, 0.5f));
    _tileMap->setPosition(Point(visibleSize.width / 2 , visibleSize.height / 2));
    _tileMap->setScale(settings::GameScene::_tile_delta_rate);
    log("aft:%f %f", _tileMap->getTileSize().height, _tileMap->getMapSize().width);
    
    _meta = _tileMap->getLayer("Unbroken");
    _background = _tileMap->getLayer("Background");
    addChild(_tileMap, -1);
    
    // 注意坐标位置差
    float offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate)/ 2;
    float offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
    TMXObjectGroup *objects = _tileMap->getObjectGroup("player");
    CCASSERT(nullptr != objects, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint1");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    int x = spawnPoint["x"].asFloat() * _tile_delta_rate;
    int y = spawnPoint["y"].asFloat() * _tile_delta_rate;
    
    
    /*** add sprite***/
    _myplayer = character::create(character::MAPLE_WISH);
    _myplayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _myplayer->setPosition(offx + x, offy + y);
    addChild(_myplayer, 1);
    
    
    
    // basic bubbles
    _my_bubbles = 0;
    
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

/*****键盘监听*****/
void GameScene::myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    GameScene::_optionCode code = DEFAULT;
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
    // TODO:走路可以用状态机实现
    if (code != DEFAULT) {
        for (auto &b : _my_sprite_move)     b = false;
        _my_sprite_move[code] = true;       //有移动的趋势, 防止爆栈
        
        // animation and direction
        std::string next_direction(_myplayer->_spriteName + "_"+ std::string(direc_string[code]) +"_");
        auto tmp_f = SpriteFrameCache::getInstance()->getSpriteFrameByName(next_direction + "01.png");
        _myplayer->setSpriteFrame(tmp_f);

        
        auto anime = getAnimationByName(next_direction, 0.1f, _myplayer->_animation_frames);
        auto animate = Animate::create(anime);
        auto player_action = RepeatForever::create(animate);
        _myplayer->runAction(player_action);
    }
}



void GameScene::myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    GameScene::_optionCode key;
    enum T {
        GO_CODE, BUBBLE_CODE
    } code;
    code = GO_CODE;     //默认为go_code
    
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            key = _optionCode::GO_UP;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            key = _optionCode::GO_DOWN;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            key = _optionCode::GO_LEFT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            key = _optionCode::GO_RIGHT;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            code = BUBBLE_CODE;
            break;
        default:
            break;
    }
    
    if (code == GO_CODE) {
        _my_sprite_move[key] = false;       //有移动的趋势
        _myplayer->stopAllActions();
    }
    else if (code == BUBBLE_CODE) {
        setBubble();
    }
}

/****人物移动****/
void GameScene::mySpriteMove() {
    Vector<FiniteTimeAction *> moves;
    const int step = 5;
    float dur = 0.1f;
    //TODO: 增加边界检测
    // 获得x y 的上界 下界
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate)/ 2;
    auto offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
    auto lowerx = offx, upperx = visibleSize.width - offx;
    auto lowery = offy, uppery = visibleSize.height - offy;
    
    const static int BORDER = 2;        //边界长
    if (_my_sprite_move[GO_RIGHT]) {
        if (upperx >= _myplayer->getPosition().x + BORDER)
            if (accessAble(Vec2(_myplayer->getPosition().x + step + _myplayer->getContentSize().width / 2, _myplayer->getPosition().y)))
                moves.pushBack(MoveBy::create(dur, Vec2(step, 0)));
    }
    
    if (_my_sprite_move[GO_LEFT]) {
        if (lowerx <= _myplayer->getPosition().x - BORDER)
            if (accessAble(Vec2(_myplayer->getPosition().x - step - _myplayer->getContentSize().width / 2, _myplayer->getPosition().y)))
                moves.pushBack(MoveBy::create(dur, Vec2(-step, 0)));
    }
    
    if (_my_sprite_move[GO_UP]) {
        if (uppery >= _myplayer->getPosition().y + BORDER)
            if (accessAble(Vec2(_myplayer->getPosition().x, _myplayer->getPosition().y + step + _myplayer->getContentSize().height/ 2)))
                moves.pushBack(MoveBy::create(dur, Vec2(0, step)));
    }
    
    if (_my_sprite_move[GO_DOWN]) {
        if (lowery <= _myplayer->getPosition().y - BORDER)
            if (accessAble(Vec2(_myplayer->getPosition().x, _myplayer->getPosition().y - step - _myplayer->getContentSize().height / 2)))
                moves.pushBack(MoveBy::create(dur, Vec2(0, -step)));
    }
    
    // 有可能啥都没有2333
    if (moves.size())
        _myplayer->runAction(cocos2d::Spawn::create(moves));
}

// bubble应该设置在tilemap的grid上
// bubble渲染问题
void GameScene::setBubble() {
    if (_my_bubbles >= _myplayer->_currentBubbles) {
        return;
    }
    auto pos0 = tileCoordForPosition(_myplayer->getPosition());
//    pos0.x = static_cast<int>(pos0.x); pos0.y = static_cast<int>(pos0.y);
    auto mySpritePos = _background->getPositionAt(pos0) * _tile_delta_rate;
    auto visibleSize = Director::getInstance()->getWinSize();
    mySpritePos += (visibleSize - _tileMap->getContentSize() * _tile_delta_rate) / 2;

    // DEBUG : not mySpritePos
    if (accessAble(_myplayer->getPosition())) {
        // TODO: 调整精灵位置
        auto newBubble = Bubbles::create(_myplayer->_currentPower);
        newBubble->setAnchorPoint(Vec2::ZERO);
        newBubble->setScale(_tile_delta_rate);
        
        // DEBUG: 判断泡泡放置是否是accessable 的
        newBubble->setPosition(mySpritePos);
        auto timeBoom = CallFuncN::create(CC_CALLBACK_1(GameScene::BubbleBoom, this));
        
        // 动画(是否可以抽象)
        auto anime = getAnimationByName("Popo_", 0.25, bubble_frame_nums);
        
        auto animate = Animate::create(anime);
        auto bubbleAction = RepeatForever::create(animate);
        newBubble->runAction(bubbleAction);
        
        addChild(newBubble);
        ++_my_bubbles;
        newBubble->runAction(Sequence::create(DelayTime::create(3), timeBoom, NULL));
    }
}

// 泡泡爆炸, 可以添加逻辑
void GameScene::BubbleBoom(Ref* sender) {
    Sprite *sprite = dynamic_cast<Sprite*>(sender);
    --_my_bubbles;
    this->removeChild(sprite);
}

void GameScene::update(float dt) {
    mySpriteMove();
}

cocos2d::Vec2 GameScene::tileCoordForPosition(cocos2d::Vec2 pos) {
    auto visibleSize = Director::getInstance()->getWinSize();
    auto offx = (visibleSize.width - static_cast<float>(_tileMap->getContentSize().width * _tile_delta_rate))/ 2;
    auto offy = (visibleSize.height - static_cast<float>(_tileMap->getContentSize().height * _tile_delta_rate))/ 2;
    
    /*** test ***/
    
    // 玩家位置的y除以地图的高，得到的是地图纵向第几个格子（tile），
    // 但是因为cocos2d-x的y轴（左下角）和TileMap的y轴（左上角）轴相反，所以使用地图的高度减去玩家位置的y
    
    float pointHeight = _tileMap->getTileSize().height * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR();
    int x = (int)((pos.x - offx) / (_tileMap->getTileSize().width * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR()));
    
//    int y = (int)((_tileMap->getMapSize().height * _tile_delta_rate * pointHeight - pos.y - offy) / pointHeight);
    int y = static_cast<int>((visibleSize.height - offy - pos.y) / pointHeight);
    if (y > 14) y = 14;
    if (x > 14) x = 14;
    log("coord : %d %d", x, y);
    return Vec2(x,y);
    
    // DEBUG
//    float x = (pos.x - offx) / (_tileMap->getTileSize().width * _tile_delta_rate);
//    // TODO: find what was fucking wrong with this bullshit position
//    float y = (pos.y - offy) / (_tileMap->getTileSize().height * _tile_delta_rate) - 0.3; // 原先-0.3
//    if (14 - y > 14)
//        y = 0;
//    return Vec2(x + 1, 14 - y);
}

bool GameScene::accessAble(cocos2d::Vec2 pos) {
    Vec2 tileCoord = tileCoordForPosition(pos);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto propertiy = _tileMap->getPropertiesForGID(tileGid);
        if (propertiy.isNull()) //
            return false;
        auto properties = propertiy.asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collidable"].asString();
            if ("True" == collision) {
                return false;
            }
        }
    }
    return true;
}

// 通过名字获取动画, 第二个参数为播放属性, 第三个参数为张数目, 从1开始
Animation* GameScene::getAnimationByName(std::string animName,float delay,int animNum){
    auto animation = Animation::create();
    // 循环从精灵帧缓存中获取与图片名称相对应的精灵帧组成动画
    for(unsigned int i = 1;i<animNum;i++){
        // 获取动画图片名称，例如plane0.png
        std::string frameName = animName;
        frameName.append(StringUtils::format("%02d",i)).append(".png");
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName.c_str()));
    }
    // 设置动画播放的属性
    animation->setDelayPerUnit(delay);
    // 让精灵对象在动画执行完后恢复到最初状态
    animation->setRestoreOriginalFrame(true);
    // 返回动画对象
    return animation;
}

