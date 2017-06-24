// TODO: 改变遮挡关系
#include "GameScene.h"
#include "Bubbles.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "CommonUse.h"
#include <random>
#include "CharacterFSM.h"
#include "Character.h"
#include "../controller/PlayerController.h"
#include "BubbleController.h"
#include "PropLayer.h"
#include "PropController.h"
#include <chrono>
#include "OpenScene.h"
#include "WebClient.h"
#include "SceneManager.h"
#include "../DataManager.h"

USING_NS_CC;
using namespace ui;
using namespace settings::GameScene;

bool GameScene::initWithMap(const std::map<std::string, std::pair<int, int>>& name2pos) {
    auto b = init();
    if (!b) return b;
    for (auto &pair: name2pos) {
        this->addCharacter(pair.second.first, pair.second.second, pair.first);
    }
    return true;
}

cocos2d::Layer* createLayerWithMap(const std::map<std::string, std::pair<int, int>>& name2pos) {
    auto layer = new GameScene();
    if (layer && layer->initWithMap(name2pos)) {
        layer->autorelease();
        return layer;
    } else {
        delete layer;
        layer = nullptr;
        return layer;
    }
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto game_layer = GameScene::create();
    
    
    // temporary set it ten
    game_layer->setName("GameScene");
    game_layer->setTag(10);
    
    // add layer as a child to scene
    scene->addChild(game_layer);
    
    
    // return the scene
    return scene;
}


void GameScene::addCharacter(int index, int type, const std::string &name) {
    
    CCASSERT(nullptr != objects, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint" + std::to_string(index));
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    float x = spawnPoint["x"].asFloat() * _tile_delta_rate;
    float y = spawnPoint["y"].asFloat() * _tile_delta_rate;
    auto player = character::create(static_cast<character::characterType>(type));
    player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    player->setPosition(offx + x, offy + y);
    // if it is my chara
    if (name == DataManager::getInstance()->getStringForKey("MyName")) {
        _myplayer = player;
        _myplayer->setTag(20);
        _myplayer->setName("myplayer");
    }
    player->changeState(std::make_shared<CharStand>());
    _game_players.pushBack(player);
    name2chara.insert(name, player);
    addChild(player, 1);
    
    
}

cocos2d::Scene* GameScene::createSceneWithMap(const std::map<std::string, std::pair<int, int>>& name2pos)
{
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto game_layer = createLayerWithMap(name2pos);
    
    
    // temporary set it ten
    game_layer->setName("GameScene");
    game_layer->setTag(10);
    
    // add layer as a child to scene
    scene->addChild(game_layer);
    
    // return the scene
    return scene;
}

// static function, GET CURRENT GAME SCENE
GameScene* GameScene::getCurrentMap() {
    auto currentScene = Director::getInstance()->getRunningScene();
    return dynamic_cast<GameScene*>(currentScene->getChildByName("GameScene"));
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	// a temporary background
	auto backG = Sprite::create("BackGround/Cool_background.jpg");
	addChild(backG, -10);
	backG->setPosition(visibleSize / 2);

	/***** tilemap ******/
    std::string tilename =
    "gameStart/map" +
    DataManager::getInstance()->getStringForKey("map") +
    ".tmx";
	_tileMap = TMXTiledMap::create(tilename);
	_tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	_tileMap->setScale(settings::GameScene::_tile_delta_rate);

	_meta = _tileMap->getLayer("Unbroken");
	_background = _tileMap->getLayer("Background");
	addChild(_tileMap, -1);

	// 注意坐标位置差
	offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate) / 2;
	offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
    objects = _tileMap->getObjectGroup("player");
	
    CCASSERT(nullptr != objects, "'Objects' object group not found");
	auto spawnPoint = objects->getObject("SpawnPoint1");
	CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
	float x = spawnPoint["x"].asFloat() * _tile_delta_rate;
	float y = spawnPoint["y"].asFloat() * _tile_delta_rate;

	tileLoadProps();

	
    // bubbles start from 0

	// add controller
	auto playerController = PlayerController::create();
	addChild(playerController);
	auto bubbleController = BubbleController::create();
	addChild(bubbleController);
	// add prop layer
	log("CameScene_prop111");
	auto propLayer = PropLayer::create();
	propLayer->setName("PropLayer");
	addChild(propLayer);
	log("CameScene_prop");
    controllers[0] = bubbleController, controllers[1] = playerController;
    auto propController = PropController::create();
    propController->setName("PropController");
    addChild(propController);
    
	this->scheduleUpdate();
	return true;
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



/****人物移动****/
void GameScene::CharacterMove(character* chara) {
    //TODO: 增加边界检测
    // 获得x y 的上界 下界
    const static float lowerx = offx + 3, upperx = visibleSize.width - offx;
    const static float lowery = offy + 3, uppery = visibleSize.height - offy;
    const static Vec2 delta_rate = Vec2{0, 3};
    
    auto in_tile_map = [&](Vec2 pos)->bool{
        if (pos.x >= lowerx && pos.x <= upperx)
            if (pos.y >= lowery && pos.y <= uppery)
                return true;
        return false;
    };
    
    const static float basic_step = 1.8;
    
    
    int cur_velocity = chara->isRiding()? chara->getRidingSpeed(): chara->_currentVelocity;
    float curstep = cur_velocity  / 3.0 + basic_step;
    // UP, DOWN, LEFT, RIGHT
    Vec2 delta_pos[4]{Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0)};
    // 判断动作，调整step
    // get exact direction and last move
    
    for (int index = 0; index < 4; ++index) {
        if (!chara->_chara_move[index]) {
            continue;
        }
        Vec2 cur_delta = delta_pos[index];
        auto test_point = cur_delta;
        bool walk(true);           // really move?
        auto deltas = chara->get_collection_point(index);
        auto pos1 = deltas.first, pos2 = deltas.second;
        if (!in_tile_map(pos1 + test_point) || !in_tile_map(pos2 + test_point)) {
            break;
        } else if (!hasCollisionInGridPos(tileCoordForPosition(pos1 + test_point)) || !hasCollisionInGridPos(tileCoordForPosition(pos2 + test_point))) {
            walk = false;
        }
        
        if (hasCollideableBubble(tileCoordForPosition(pos1 + test_point + delta_rate)) || hasCollideableBubble(tileCoordForPosition(pos2 + test_point + delta_rate))) {
            if (tileCoordForPosition(pos1) != tileCoordForPosition(pos2 + test_point + delta_rate)) {\
                walk = false;
            }
        }
        if (walk) {
            chara->setPosition(chara->getPosition() + cur_delta);
        }
        break;
    }
}

// bubble应该设置在tilemap的grid上
// bubble渲染问题
void GameScene::setBubble(character* chara) {
    
    if (chara->curSetBubbles >= chara->_currentBubbles) {
        return;
    }
    // TODO: duplicate here!!
    auto pos0 = tileCoordForPosition(chara->getPosition());
    if (chara->getAnchorPoint() != Vec2::ZERO) {
        if (pos0.x > 14) pos0.x = 14;
    }
    // TODO: find out what was wrong
    if (pos0.y > 14) pos0.y = 14;
    
    auto mySpritePos = PositionForTileCoord(tileCoordForPosition(chara->getPosition()));

    // DEBUG : not mySpritePos
    auto mypos = chara->getPosition();
    if (!hasBubble(tileCoordForPosition(mypos)) && accessAble(mypos)) {
        // 调整精灵位置
        auto newBubble = Bubbles::create(chara->_currentPower, chara);
        newBubble->setAnchorPoint(Vec2::ZERO);
        newBubble->setScale(_tile_delta_rate);
        
        // DEBUG: 判断泡泡放置是否是accessable 的
        newBubble->setPosition(mySpritePos);
        // 动画(是否可以抽象)
        runAnimationByName(newBubble, "Popo_", 0.25, bubble_frame_nums);
        _map_screen_bubbles[pos0] = newBubble;
        addChild(newBubble);
        ++chara->curSetBubbles;
    }
}



// 泡泡爆炸, 可以添加逻辑
void GameScene::BubbleBoom(Ref* sender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    float volume = DataManager::getInstance()->getFloatForKey("effectPercent");
    audio->setEffectsVolume(volume);
    audio->playEffect("effect/explode.wav", false);
    auto *sprite = dynamic_cast<Bubbles*>(sender);
    auto beg_pos = sprite->getPosition();
    int power = sprite->get_power();
    
    if (_game_players.find(sprite->setterCharacter) != _game_players.end())
        --sprite->setterCharacter->curSetBubbles;
    
    
    this->removeChild(sprite);
    for (auto iter = _map_screen_bubbles.begin(); iter != _map_screen_bubbles.end(); ++iter) {
        if (iter->second == sprite) {
            _map_screen_bubbles.erase(iter);
            break;
        }
    }
    /***爆炸逻辑***/
    auto pos = tileCoordForPosition(beg_pos);
    for (auto chara: _game_players) {
        // pay attention the guard
        if (chara->isGuard()) {
            continue;
        }
        auto chara_pos = tileCoordForPosition(chara->getPosition());
        chara_pos.y += 1;
        if (chara_pos == pos) {
            log("fired");
            chara->charaFired();
        }
        removePositionItem(pos);
    }
    add_and_clear_with_time(Sprite::create(center_boom), boom_time, beg_pos);
    horizontal_boom(beg_pos, power);
    vertival_boom(beg_pos, power);
}

void GameScene::update(float dt) {
    static std::string myname = DataManager::getInstance()->getStringForKey("MyName ");
    if (_myplayer) {
        int i;
        for (i = 0; i < 4; ++i) {
            if (_myplayer->_chara_move[i])
                break;
        }
        
        // i == 4: 不变向
        // send: "state name pos x y"
        std::string s = std::to_string(i) + " " + std::to_string(_myplayer->getPosition().x) + " " + std::to_string(_myplayer->getPosition().y);
        log("dir : %d", i);
        WebClient::getInstance()->send_data("state " + myname + s);
    }
    for (auto chara : _game_players) {
        chara->excute();
    }
    
}

/**** coord convert ****/
cocos2d::Vec2 GameScene::PositionForTileCoord(cocos2d::Vec2 pos) {
    if (_myplayer->getAnchorPoint() != Vec2::ZERO) {
        if (pos.x > 14) pos.x = 14;
    }
    // TODO: find out what was wrong
    if (pos.y > 14) pos.y = 14;
    auto mySpritePos = _background->getPositionAt(pos) * _tile_delta_rate;
    auto visibleSize = Director::getInstance()->getWinSize();
    mySpritePos += (visibleSize - _tileMap->getContentSize() * _tile_delta_rate) / 2;
    return mySpritePos;
}

cocos2d::Vec2 GameScene::tileCoordForPosition(cocos2d::Vec2 pos) {
    // 玩家位置的y除以地图的高，得到的是地图纵向第几个格子（tile），
    // 但是因为cocos2d-x的y轴（左下角）和TileMap的y轴（左上角）轴相反，所以使用地图的高度减去玩家位置的y
    float pointHeight = _tileMap->getTileSize().height * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR();
    int x = (int)((pos.x - offx) / (_tileMap->getTileSize().width * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR()));
    int y = static_cast<int>((visibleSize.height - offy - pos.y) / pointHeight);
    if (x > 14) x = 14;
    return Vec2(x,y);
}

/***
 检测是否可以到达
 in: cocos2d pos
 out: 是否与不可碰墙壁的发生碰撞
 attention: 只要求有泡泡
 ***/
bool GameScene::accessAble(cocos2d::Vec2 pos) {
    Vec2 tileCoord = tileCoordForPosition(pos);
    // TODO: find out what was wrong
    if (tileCoord.x < 0 || tileCoord.y < 0)
        return false;
    if (hasCollisionInGridPos(tileCoord) && !hasCollideableBubble(tileCoord))
        return true;
    return false;
    
}

bool GameScene::hasCollisionInGridPos(Vec2 tileCoord) {
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto propertiy = _tileMap->getPropertiesForGID(tileGid);
        if (propertiy.isNull())
            return false;
        auto properties = propertiy.asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collidable"].asString();
            if ("true" == collision) {
                return false;
            }
        }
    }
    return true;
}


void GameScene::add_and_clear_with_time(cocos2d::Sprite* sp, float dt, Vec2 pos) {
    sp->setAnchorPoint(Vec2::ZERO);
    sp->setPosition(pos);
    sp->setScale(_tile_delta_rate);
    this->addChild(sp);
    sp->runAction(Sequence::create(DelayTime::create(dt), CallFuncN::create(CC_CALLBACK_1(GameScene::spriteToClear, this)),NULL));
}


void GameScene::spriteToClear(cocos2d::Ref* psender) {
    Sprite *sprite = dynamic_cast<Sprite*>(psender);
    this->removeChild(sprite);
}


static inline bool in_map(int x, int y) {
    if (x >= 0 && x < 15)
        if (y >= 0 && y < 15)
            return true;
    return false;
}

void GameScene::boom_animate(cocos2d::Vec2 pos, int power, int r_vec) {
    /*
     args: pos->position of sprite, power:power of bubble, vector:direction
     */
    auto tiled_position = tileCoordForPosition(pos);
    --tiled_position.y;
    static auto std_delta = Vec2(offx, offy);
    
    // dir: 0->horizontal, 1->vertical;
    Vec2 dirs[] = {Vec2(1, 0), Vec2(0, 1)};
    // 正负方向和该方向是否停止
    int syn[] = {-1, 1};
    bool synb[] = {true, true};
    for (int i = 1; i <= power; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!synb[j])
                continue;
            // 获取下一个爆炸的位置
            auto next_p = dirs[r_vec] * syn[j] * i + tiled_position;
            removePositionItem(next_p);

            // 判断爆炸位置是否在地图中
            if (!in_map(next_p.x, next_p.y)) {
                synb[j] = false;
                continue;
            }
            // 是否扩展
            bool ans(false);
            if (check_chain_boom(next_p)) {
                // chain booming!!!
            } else if (!hasCollisionInGridPos(next_p) && !prop_gotton[next_p.x][next_p.y]) {
                // have tile
                // need delay time and broken animation
                prop_gotton[next_p.x][next_p.y] = true;
                this->runAction(Sequence::create(DelayTime::create(0.2f), CallFuncN::create(
                      [=](Ref* sender) {
                          _meta->removeTileAt(next_p);
                          if (prop_on_map[next_p.x][next_p.y] < GameItem::toolNumbers) {
                              this->addItems(next_p, static_cast<GameItem::ItemTools>(prop_on_map[next_p.x][next_p.y]));
                          }
                      }), NULL));
            } else {
                // check if someone dead
                auto new_blaze = Sprite::create(boom_anime[r_vec]);
                auto mySpritePos = _background->getPositionAt(next_p) * _tile_delta_rate + std_delta;
                for (auto &chara: _game_players) {
                    if (typeid(*(chara->mCurState)) == typeid(CharGuard)) {
                        continue;
                    }
                    if (tileCoordForPosition(chara->getPosition()) == next_p) {
                        // chara was fired
//                        log("fired");
                        chara->charaFired();
                    }
                }
                ans = true;
                add_and_clear_with_time(new_blaze, boom_time, mySpritePos);
            }
            synb[j] = ans;
        }
    }
}

void GameScene::horizontal_boom(cocos2d::Vec2 pos, int power) {
    boom_animate(pos, power, 1);
}

void GameScene::vertival_boom(cocos2d::Vec2 pos, int power) {
    boom_animate(pos, power, 0);
}


bool GameScene::check_chain_boom(cocos2d::Vec2 blaze_pos) {
    auto bubbleIter = _map_screen_bubbles.find(blaze_pos);
    if (bubbleIter != _map_screen_bubbles.end()) {
        auto bubble = bubbleIter->second;
        _map_screen_bubbles.erase(bubbleIter);
        bubble->stopAllActions();
        BubbleBoom(bubble);
        return true;
    }
    return false;
}

/** 对给出的瓦片地图坐标，有精灵就返回精灵，没有就返回nullptr **/
Bubbles* GameScene::hasCollideableBubble(cocos2d::Vec2 tilePos) {
    auto bubble = hasBubble(tilePos);
    if (bubble != nullptr && bubble->isCollideable())
        return bubble;
    return nullptr;
}

Bubbles* GameScene::hasBubble(cocos2d::Vec2 tilePos) {
    auto bubbleIter = _map_screen_bubbles.find(tilePos);
    Bubbles* bubble = nullptr;
    if (bubbleIter != _map_screen_bubbles.end()) {
        bubble = bubbleIter->second;
    }
    return bubble;
}

void GameScene::addItems(cocos2d::Vec2 tiledPos, GameItem::ItemTools item_kind) {
    // 如果有道具就不再添加(多个同时爆炸？)
    auto pos = PositionForTileCoord(tiledPos);
    
    auto item = GameItem::createWithType(item_kind);
    item->setScale(_tile_delta_rate);
    item->setAnchorPoint(Vec2::ZERO);
    item->setPosition(pos);
    // DEBUG: NOT SET ANIME HERE
    
    if (screenItems.find(tiledPos) == screenItems.end())
        screenItems[tiledPos] = item;
    
    this->addChild(item);
    
}


void GameScene::tileLoadProps() {
//    static std::random_device rd;
//    static std::uniform_int_distribution<int> dist(0, GameItem::toolNumbers * 5 / 3);
    srand(DataManager::getInstance()->getIntegerForKey("PropSeed"));
    // 加载地图的对应的道具
    for (int x = 0; x < 15; ++x)
        for (int y = 0; y < 15; ++y)
            if (!hasCollisionInGridPos(Vec2(x, y))) {
                prop_on_map[x][y] = rand() % (GameItem::toolNumbers * 5 / 3);
            }
    
}


void GameScene::checkGetItem(character* chara) {
    auto tiledCharaPos = tileCoordForPosition(chara->getPosition());
    auto itemIter = screenItems.find(tiledCharaPos);
    if (itemIter != screenItems.end()) {
        auto item = itemIter->second;
        item->getItem(chara);
        screenItems.erase(itemIter);
        this->removeChild(item);
    }
}

void GameScene::removePositionItem(const Vec2 pos) {
    auto itemIter = screenItems.find(pos);
    if (itemIter != screenItems.end()) {
        auto item = itemIter->second;
        screenItems.erase(itemIter);
        this->removeChild(item);
    }
}

void GameScene::RemoveCharacter(character* chara) {
    _game_players.eraseObject(chara);
    this->removeChild(chara);
    // TODO:这里需要重新描述，注意修改
    if (_game_players.size() == 0) {
        // 游戏没有玩家
        log("game over");
    }
}

bool GameScene::checkCollisionWithOther(character* chara) {
    auto pos = tileCoordForPosition(chara->getPosition());
    for (auto c: _game_players) {
        if (c == chara) {
            continue;
        }
        else if (tileCoordForPosition(c->getPosition()) == pos) {
            // 正在碰撞
            return true;
        }
    }
    return false;
}

void GameScene::Win() {
    //增加音效
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    float volume = DataManager::getInstance()->getFloatForKey("effectPercent");
    audio->setEffectsVolume(volume);
    audio->playEffect("effect/win.wav", false);
    gameOver("Play Again");
}

void GameScene::Lose() {
    //增加音效
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    float volume = DataManager::getInstance()->getFloatForKey("effectPercent");
    audio->setEffectsVolume(volume);
    audio->playEffect("effect/lose.wav", false);
    gameOver("Game Win");
}
// 游戏结束
void GameScene::gameOver(const std::string &message) {
    // 获得设备可见视图大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto backGround = cocos2d::Sprite::create("BackGround/temple of times.png");
    backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround, 0);
    // “重新开始”按钮
    auto restart_button = Button::create("GameUI/button.png");
    restart_button->setScale(2);
    restart_button->setTitleText(message);
    restart_button->setTitleFontName("Arial");
    restart_button->setTitleFontSize(16);
    restart_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.7));
    restart_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            SceneManager::toCharaSelect();
//            auto transition = TransitionFadeBL::create(2.0, GameScene::createScene());
//            Director::getInstance()->replaceScene(transition);
        }
    });
    this->addChild(restart_button, 1);
    
    // “返回主菜单”按钮
    auto back_button = Button::create("GameUI/button.png");
    back_button->setScale(2);
    back_button->setTitleText("Return Menu");
    back_button->setTitleFontName("Arial");
    back_button->setTitleFontSize(16);
    back_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.4));
    back_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            SceneManager::toCharaSelect();
        }
    });
    this->addChild(back_button, 1);
}
