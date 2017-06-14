<<<<<<< HEAD
// TODO: ¸Ä±äÕÚµ²¹ØÏµ
=======
ï»¿// TODO: æ”¹å˜é®æŒ¡å…³ç³»
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
#include "GameScene.h"
#include "Bubbles.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "CommonUse.h"
#include <random>
#include "CharacterFSM.h"
#include "Character.h"
#include "WebClient.h"
#include "PlayerController.h"
#include "BubbleController.h"
#include "CharacterSelect.h"
#include "OpenScene.h"
#include "PropLayer.h"
#include "PropController.h"

USING_NS_CC;
using namespace settings::GameScene;
using namespace ui;

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

// static function, GET CURRENT GAME SCENE
GameScene* GameScene::getCurrentMap() {
	auto currentScene = Director::getInstance()->getRunningScene();
	return dynamic_cast<GameScene*>(currentScene->getChildByName("GameScene"));
}

bool GameScene::init()
{
<<<<<<< HEAD
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    addCloseMenu();
    //
//    auto web_layer = WebClient::create();
//    this->addChild(web_layer);
    
    // a temporary background
    auto backG = Sprite::create(backGroundPicture);
    addChild(backG, -10);
    backG->setPosition(visibleSize / 2);
    
    /***** tilemap ******/
    _tileMap = TMXTiledMap::create("gameStart/map01.tmx");
    _tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _tileMap->setPosition(Point(visibleSize.width / 2 , visibleSize.height / 2));
    _tileMap->setScale(settings::GameScene::_tile_delta_rate);
    
    _meta = _tileMap->getLayer("Unbroken");
    _background = _tileMap->getLayer("Background");
    addChild(_tileMap, -1);
    
    // ×¢Òâ×ø±êÎ»ÖÃ²î
    offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate)/ 2;
    offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
    TMXObjectGroup *objects = _tileMap->getObjectGroup("player");
    CCASSERT(nullptr != objects, "'Objects' object group not found");
    auto spawnPoint = objects->getObject("SpawnPoint1");
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
    float x = spawnPoint["x"].asFloat() * _tile_delta_rate;
    float y = spawnPoint["y"].asFloat() * _tile_delta_rate;
    
    tileLoadProps();
    
    /*** add character***/
    _myplayer = character::create(character::CHRIS);
    _myplayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _myplayer->setPosition(offx + x, offy + y);
    _myplayer->setTag(20);
    _myplayer->setName("myplayer");
    // test
//    _myplayer->changeState(std::make_shared<CharGuard>());
    addChild(_myplayer, 1);
    _game_players.pushBack(_myplayer);
    _my_bubbles = 0;        // bubbles start from 0
    
//    // add prop layer
//    auto propLayer = PropLayer::create();
//    propLayer->setName("PropLayer");
//    auto propController = PropController::create();
//    propLayer->setName("PropController");
//    // add controller
//    auto playerController = PlayerController::create();
//    playerController->setName("PlayerController");
//    
//    auto bubbleController = BubbleController::create();
//    bubbleController->setName("BubbleController");
    
    /*** debug ***/
    auto playerController = PlayerController::create();
    playerController->setName("PlayerController");
    addChild(playerController);
    auto bubbleController = BubbleController::create();
    bubbleController->setName("BubbleController");
    addChild(bubbleController);
    
    // add prop layer
    auto propLayer = PropLayer::create();
    propLayer->setName("PropLayer");
    addChild(propLayer);
    auto propController = PropController::create();
    addChild(propController);
    
//    addChild(propController);
//    addChild(propLayer);
//    addChild(bubbleController);
//    addChild(playerController);
    this->scheduleUpdate();
    
    return true;
=======
	if (!Layer::init())
	{
		return false;
	}


	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addCloseMenu();
	//
	//    auto web_layer = WebClient::create();
	//    this->addChild(web_layer);

	// a temporary background
	auto backG = Sprite::create(backGroundPicture);
	addChild(backG, -10);
	backG->setPosition(visibleSize / 2);

	/***** tilemap ******/
	_tileMap = TMXTiledMap::create("gameStart/map01.tmx");
	_tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	_tileMap->setScale(settings::GameScene::_tile_delta_rate);

	_meta = _tileMap->getLayer("Unbroken");
	_background = _tileMap->getLayer("Background");
	addChild(_tileMap, -1);

	// æ³¨æ„åæ ‡ä½ç½®å·®
	offx = (visibleSize.width - _tileMap->getContentSize().width * _tile_delta_rate) / 2;
	offy = (visibleSize.height - _tileMap->getContentSize().height * _tile_delta_rate) / 2;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("player");
	CCASSERT(nullptr != objects, "'Objects' object group not found");
	auto spawnPoint = objects->getObject("SpawnPoint1");
	CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
	float x = spawnPoint["x"].asFloat() * _tile_delta_rate;
	float y = spawnPoint["y"].asFloat() * _tile_delta_rate;

	tileLoadProps();

	/*** add character***/
	character::characterType TYPE;
	int i = UserDefault::getInstance()->getIntegerForKey("PLAYER");
	log("integer is %d", i);
	switch (i) {
	case 1:
		TYPE = character::MAPLE_WISH;
		break;
	case 2:
		TYPE = character::CHRIS;
		break;
	case 3:
		TYPE = character::SHADOWFOX;
		break;
	}
	_myplayer = character::create(TYPE);
	_myplayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_myplayer->setPosition(offx + x, offy + y);
	_myplayer->setTag(20);
	_myplayer->setName("myplayer");
	addChild(_myplayer, 1);
	_game_players.pushBack(_myplayer);
	_my_bubbles = 0;        // bubbles start from 0

							// test
							//    addItems(Vec2(10, 10));



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

	this->scheduleUpdate();

	return true;
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
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
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 1);
}

/****ÈËÎïÒÆ¶¯****/
void GameScene::CharacterMove(character* chara) {
<<<<<<< HEAD
    //TODO: Ôö¼Ó±ß½ç¼ì²â
    // »ñµÃx y µÄÉÏ½ç ÏÂ½ç
    const static float lowerx = offx + 3, upperx = visibleSize.width - offx;
    const static float lowery = offy + 3, uppery = visibleSize.height - offy;
    const static Vec2 delta_rate = Vec2{0, -10};
    
    auto in_tile_map = [&](Vec2 pos)->bool{
        if (pos.x >= lowerx && pos.x <= upperx)
            if (pos.y >= lowery && pos.y <= uppery)
                return true;
        return false;
    };
    
    const static float basic_step = 1.8;
    float curstep = chara->_currentVelocity  / 3.0 + basic_step;
    
    // UP, DOWN, LEFT, RIGHT
    Vec2 delta_pos[4]{Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0)};
    // ÅĞ¶Ï¶¯×÷£¬µ÷Õûstep
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
        } else if (!accessAble(pos1 + test_point) || !accessAble(pos2 + test_point)) {
            walk = false;
        }
        
        if (hasBubble(tileCoordForPosition(pos1 + test_point + delta_rate)) || hasBubble(tileCoordForPosition(pos2 + test_point + delta_rate))) {
            walk = false;
        }
        if (walk) {
            chara->setPosition(chara->getPosition() + cur_delta);
        }
        break;
    }
=======
	//TODO: å¢åŠ è¾¹ç•Œæ£€æµ‹
	// è·å¾—x y çš„ä¸Šç•Œ ä¸‹ç•Œ
	const static float lowerx = offx + 3, upperx = visibleSize.width - offx;
	const static float lowery = offy + 3, uppery = visibleSize.height - offy;
	const static Vec2 delta_rate = Vec2{ 0, -10 };

	auto in_tile_map = [&](Vec2 pos)->bool {
		if (pos.x >= lowerx && pos.x <= upperx)
			if (pos.y >= lowery && pos.y <= uppery)
				return true;
		return false;
	};

	const static float basic_step = 1.8;
	float curstep = chara->_currentVelocity / 3.0 + basic_step;

	// UP, DOWN, LEFT, RIGHT
	Vec2 delta_pos[4]{ Vec2(0, curstep), Vec2(0, -curstep), Vec2(-curstep, 0), Vec2(curstep, 0) };
	// åˆ¤æ–­åŠ¨ä½œï¼Œè°ƒæ•´step
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
		}
		else if (!accessAble(pos1 + test_point) || !accessAble(pos2 + test_point)) {
			walk = false;
		}

		if (hasBubble(tileCoordForPosition(pos1 + test_point + delta_rate)) || hasBubble(tileCoordForPosition(pos2 + test_point + delta_rate))) {
			walk = false;
		}
		if (walk) {
			chara->setPosition(chara->getPosition() + cur_delta);
		}
		break;
	}
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
}

// bubbleÓ¦¸ÃÉèÖÃÔÚtilemapµÄgridÉÏ
// bubbleäÖÈ¾ÎÊÌâ
void GameScene::setBubble(character* chara) {
<<<<<<< HEAD
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
    auto mypos = _myplayer->getPosition();
    if (accessAble(mypos)) {
        // µ÷Õû¾«ÁéÎ»ÖÃ
        auto newBubble = Bubbles::create(_myplayer->_currentPower, chara);
        newBubble->setAnchorPoint(Vec2::ZERO);
        newBubble->setScale(_tile_delta_rate);
        
        // DEBUG: ÅĞ¶ÏÅİÅİ·ÅÖÃÊÇ·ñÊÇaccessable µÄ
        newBubble->setPosition(mySpritePos);
        auto timeBoom = CallFuncN::create(CC_CALLBACK_1(GameScene::BubbleBoom, this));
        
        // ¶¯»­(ÊÇ·ñ¿ÉÒÔ³éÏó)
        runAnimationByName(newBubble, "Popo_", 0.25, bubble_frame_nums);
        newBubble->runAction(Sequence::create(DelayTime::create(0.3),CallFuncN::create(
                            [=](Ref* sender) {
                                _map_screen_bubbles[pos0] = newBubble;
                            }), DelayTime::create(2.7), timeBoom, NULL));
        addChild(newBubble);
        ++chara->curSetBubbles;
        
    }
=======
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
	auto mypos = _myplayer->getPosition();
	if (accessAble(mypos)) {
		// è°ƒæ•´ç²¾çµä½ç½®
		auto newBubble = Bubbles::create(_myplayer->_currentPower, chara);
		newBubble->setAnchorPoint(Vec2::ZERO);
		newBubble->setScale(_tile_delta_rate);

		// DEBUG: åˆ¤æ–­æ³¡æ³¡æ”¾ç½®æ˜¯å¦æ˜¯accessable çš„
		newBubble->setPosition(mySpritePos);
		auto timeBoom = CallFuncN::create(CC_CALLBACK_1(GameScene::BubbleBoom, this));

		// åŠ¨ç”»(æ˜¯å¦å¯ä»¥æŠ½è±¡)
		runAnimationByName(newBubble, "Popo_", 0.25, bubble_frame_nums);
		addChild(newBubble);



		++chara->curSetBubbles;
		newBubble->runAction(Sequence::create(DelayTime::create(0.3), CallFuncN::create(
			[=](Ref* sender) {
			_map_screen_bubbles[pos0] = newBubble;
		}), DelayTime::create(2.7), timeBoom, NULL));
	}
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
}



// ÅİÅİ±¬Õ¨, ¿ÉÒÔÌí¼ÓÂß¼­
void GameScene::BubbleBoom(Ref* sender) {
<<<<<<< HEAD
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
    /***±¬Õ¨Âß¼­***/
    auto pos = tileCoordForPosition(beg_pos);
    for (auto chara: _game_players) {
        // pay attention the guard
        if (chara->isGuard()) {
            continue;
        }
        auto chara_pos = tileCoordForPosition(chara->getPosition());
        chara_pos.y += 1;
        if (chara_pos == pos)
            chara->changeState(std::make_shared<CharStuck>());
    }
    add_and_clear_with_time(Sprite::create(center_boom), boom_time, beg_pos);
    horizontal_boom(beg_pos, power);
    vertival_boom(beg_pos, power);
=======
	//æ·»åŠ éŸ³æ•ˆ
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume = UserDefault::getInstance()->getFloatForKey("effectPercent");
	audio->setEffectsVolume(volume);
	audio->playEffect("effect/explode.wav", false);

	auto *sprite = dynamic_cast<Bubbles*>(sender);
	auto beg_pos = sprite->getPosition();
	int power = sprite->get_power();
	
	if (_game_players.find(sprite->setterCharacter) != _game_players.end())
		--(sprite->setterCharacter->curSetBubbles);

	this->removeChild(sprite);
	for (auto iter = _map_screen_bubbles.begin(); iter != _map_screen_bubbles.end(); ++iter) {
		if (iter->second == sprite) {
			_map_screen_bubbles.erase(iter);
			break;
		}
	}
	/***çˆ†ç‚¸é€»è¾‘***/
	auto pos = tileCoordForPosition(beg_pos);
	for (auto chara : _game_players) {
		auto chara_pos = tileCoordForPosition(chara->getPosition());
		chara_pos.y += 1;
		if (chara_pos == pos)
			chara->changeState(std::make_shared<CharStuck>());
	}
	add_and_clear_with_time(Sprite::create(center_boom), boom_time, beg_pos);
	horizontal_boom(beg_pos, power);
	vertival_boom(beg_pos, power);
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
}

void GameScene::update(float dt) {
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
<<<<<<< HEAD
    // Íæ¼ÒÎ»ÖÃµÄy³ıÒÔµØÍ¼µÄ¸ß£¬µÃµ½µÄÊÇµØÍ¼×İÏòµÚ¼¸¸ö¸ñ×Ó£¨tile£©£¬
    // µ«ÊÇÒòÎªcocos2d-xµÄyÖá£¨×óÏÂ½Ç£©ºÍTileMapµÄyÖá£¨×óÉÏ½Ç£©ÖáÏà·´£¬ËùÒÔÊ¹ÓÃµØÍ¼µÄ¸ß¶È¼õÈ¥Íæ¼ÒÎ»ÖÃµÄy
    float pointHeight = _tileMap->getTileSize().height * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR();
    int x = (int)((pos.x - offx) / (_tileMap->getTileSize().width * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR()));
    int y = static_cast<int>((visibleSize.height - offy - pos.y) / pointHeight);
    if (x > 14) x = 14;
    return Vec2(x,y);
}

/***
 ¼ì²âÊÇ·ñ¿ÉÒÔµ½´ï
 in: cocos2d pos
 out: ÊÇ·ñÓë²»¿ÉÅöÇ½±ÚµÄ·¢ÉúÅö×²
 ***/
=======
	// ç©å®¶ä½ç½®çš„yé™¤ä»¥åœ°å›¾çš„é«˜ï¼Œå¾—åˆ°çš„æ˜¯åœ°å›¾çºµå‘ç¬¬å‡ ä¸ªæ ¼å­ï¼ˆtileï¼‰ï¼Œ
	// ä½†æ˜¯å› ä¸ºcocos2d-xçš„yè½´ï¼ˆå·¦ä¸‹è§’ï¼‰å’ŒTileMapçš„yè½´ï¼ˆå·¦ä¸Šè§’ï¼‰è½´ç›¸åï¼Œæ‰€ä»¥ä½¿ç”¨åœ°å›¾çš„é«˜åº¦å‡å»ç©å®¶ä½ç½®çš„y
	float pointHeight = _tileMap->getTileSize().height * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR();
	int x = (int)((pos.x - offx) / (_tileMap->getTileSize().width * _tile_delta_rate / CC_CONTENT_SCALE_FACTOR()));
	int y = static_cast<int>((visibleSize.height - offy - pos.y) / pointHeight);
	if (x > 14) x = 14;
	return Vec2(x, y);
}

/***
æ£€æµ‹æ˜¯å¦å¯ä»¥åˆ°è¾¾
in: cocos2d pos
out: æ˜¯å¦ä¸ä¸å¯ç¢°å¢™å£çš„å‘ç”Ÿç¢°æ’
***/
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
bool GameScene::accessAble(cocos2d::Vec2 pos) {
	Vec2 tileCoord = tileCoordForPosition(pos);
	// TODO: find out what was wrong
	if (tileCoord.x < 0 || tileCoord.y < 0)
		return false;
	if (hasCollisionInGridPos(tileCoord) && !hasBubble(tileCoord))
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
	sp->runAction(Sequence::create(DelayTime::create(dt), CallFuncN::create(CC_CALLBACK_1(GameScene::spriteToClear, this)), NULL));
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
<<<<<<< HEAD
    /*
     args: pos->position of sprite, power:power of bubble, vector:direction
     */
    auto tiled_position = tileCoordForPosition(pos);
    --tiled_position.y;
    static auto std_delta = Vec2(offx, offy);
    
    // dir: 0->horizontal, 1->vertical;
    Vec2 dirs[] = {Vec2(1, 0), Vec2(0, 1)};
    // Õı¸º·½ÏòºÍ¸Ã·½ÏòÊÇ·ñÍ£Ö¹
    int syn[] = {-1, 1};
    bool synb[] = {true, true};
    for (int i = 1; i <= power; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!synb[j])
                continue;
            // »ñÈ¡ÏÂÒ»¸ö±¬Õ¨µÄÎ»ÖÃ
            auto next_p = dirs[r_vec] * syn[j] * i + tiled_position;
            // ÅĞ¶Ï±¬Õ¨Î»ÖÃÊÇ·ñÔÚµØÍ¼ÖĞ
            if (!in_map(next_p.x, next_p.y)) {
                synb[j] = false;
                continue;
            }
            // ÊÇ·ñÀ©Õ¹
            bool ans(false);
            if (check_chain_boom(next_p)) {
                // chain booming!!!
            } else if (!hasCollisionInGridPos(next_p)) {
                // have tile
                // need delay time and broken animation
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
                        auto cur_code = typeid(*(chara->mCurState)).hash_code();
                        if (!chara->isGuard()) {
                            if (cur_code == typeid(CharStand).hash_code() || cur_code == typeid(CharMove).hash_code())
                                chara->changeState(std::make_shared<CharStuck>());
                            else if(cur_code == typeid(CharOnRiding).hash_code())
                                chara->changeState(std::make_shared<CharNormal>());
                        }   
                    }
                }
                ans = true;
                add_and_clear_with_time(new_blaze, boom_time, mySpritePos);
            }
            synb[j] = ans;
        }
    }
=======
	/*
	args: pos->position of sprite, power:power of bubble, vector:direction
	*/
	auto tiled_position = tileCoordForPosition(pos);
	--tiled_position.y;
	static auto std_delta = Vec2(offx, offy);

	// dir: 0->horizontal, 1->vertical;
	Vec2 dirs[] = { Vec2(1, 0), Vec2(0, 1) };
	// æ­£è´Ÿæ–¹å‘å’Œè¯¥æ–¹å‘æ˜¯å¦åœæ­¢
	int syn[] = { -1, 1 };
	bool synb[] = { true, true };
	for (int i = 1; i <= power; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (!synb[j])
				continue;
			// è·å–ä¸‹ä¸€ä¸ªçˆ†ç‚¸çš„ä½ç½®
			auto next_p = dirs[r_vec] * syn[j] * i + tiled_position;
			// åˆ¤æ–­çˆ†ç‚¸ä½ç½®æ˜¯å¦åœ¨åœ°å›¾ä¸­
			if (!in_map(next_p.x, next_p.y)) {
				synb[j] = false;
				continue;
			}
			// æ˜¯å¦æ‰©å±•
			bool ans(false);
			if (check_chain_boom(next_p)) {
				// chain booming!!!
			}
			else if (!hasCollisionInGridPos(next_p)) {
				// have tile
				// need delay time and broken animation
				this->runAction(Sequence::create(DelayTime::create(0.2f), CallFuncN::create(
					[=](Ref* sender) {
					_meta->removeTileAt(next_p);
					if (prop_on_map[next_p.x][next_p.y] < GameItem::toolNumbers) {
						this->addItems(next_p, static_cast<GameItem::ItemTools>(prop_on_map[next_p.x][next_p.y]));
					}
				}), NULL));
			}
			else {
				// check if someone dead
				auto new_blaze = Sprite::create(boom_anime[r_vec]);
				auto mySpritePos = _background->getPositionAt(next_p) * _tile_delta_rate + std_delta;
				for (auto &chara : _game_players) {
					if (tileCoordForPosition(chara->getPosition()) == next_p) {
						// chara was fired
						auto cur_code = typeid(*(chara->mCurState)).hash_code();
						if (cur_code == typeid(CharStand).hash_code() || cur_code == typeid(CharMove).hash_code())
							chara->changeState(std::make_shared<CharStuck>());
						else if (cur_code == typeid(CharOnRiding).hash_code())
							chara->changeState(std::make_shared<CharNormal>());
					}
				}
				ans = true;
				add_and_clear_with_time(new_blaze, boom_time, mySpritePos);
			}
			synb[j] = ans;
		}
	}
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
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

/** ¶Ô¸ø³öµÄÍßÆ¬µØÍ¼×ø±ê£¬ÓĞ¾«Áé¾Í·µ»Ø¾«Áé£¬Ã»ÓĞ¾Í·µ»Ønullptr **/
Bubbles* GameScene::hasBubble(cocos2d::Vec2 tilePos) {
	auto bubbleIter = _map_screen_bubbles.find(tilePos);
	Bubbles* bubble = nullptr;
	if (bubbleIter != _map_screen_bubbles.end()) {
		bubble = bubbleIter->second;
	}
	return bubble;
}

void GameScene::addItems(cocos2d::Vec2 tiledPos, GameItem::ItemTools item_kind) {
	auto pos = PositionForTileCoord(tiledPos);

	auto item = GameItem::create(static_cast<GameItem::ItemTools>(prop_on_map[tiledPos.x][tiledPos.y]));
	item->setScale(_tile_delta_rate);
	item->setAnchorPoint(Vec2::ZERO);
	item->setPosition(pos);
	// anime
	runAnimationByName(item, std::string(settings::Items::ItemNames[item_kind]) + "_", 0.2, 3);
	screenItems[tiledPos] = item;

	this->addChild(item);

}


void GameScene::tileLoadProps() {
<<<<<<< HEAD
    static std::random_device rd;
    static std::uniform_int_distribution<int> dist(0, GameItem::toolNumbers * 5 / 3);
    // ¼ÓÔØµØÍ¼µÄ¶ÔÓ¦µÄµÀ¾ß
    for (int x = 0; x < 15; ++x)
        for (int y = 0; y < 15; ++y)
            if (!hasCollisionInGridPos(Vec2(x, y))) {
                prop_on_map[x][y] = dist(rd);
            }
    
=======
	static std::random_device rd;
	static std::uniform_int_distribution<int> dist(0, GameItem::toolNumbers * 5 / 3);
	// åŠ è½½åœ°å›¾çš„å¯¹åº”çš„é“å…·
	for (int x = 0; x < 15; ++x)
		for (int y = 0; y < 15; ++y)
			if (!hasCollisionInGridPos(Vec2(x, y))) {
				prop_on_map[x][y] = dist(rd);
			}

>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
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

void GameScene::RemoveCharacter(character* chara) {
<<<<<<< HEAD
    _game_players.eraseObject(chara);
    this->removeChild(chara);
    // TODO:ÕâÀïĞèÒªÖØĞÂÃèÊö£¬×¢ÒâĞŞ¸Ä
    if (_game_players.size() == 0) {
        // ÓÎÏ·Ã»ÓĞÍæ¼Ò
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
            // ÕıÔÚÅö×²
            return true;
        }
    }
    return false;
}


=======
	_game_players.eraseObject(chara);
	this->removeChild(chara);
	// TODO:è¿™é‡Œéœ€è¦é‡æ–°æè¿°ï¼Œæ³¨æ„ä¿®æ”¹
	if (_game_players.size() == 0) {
		// æ¸¸æˆæ²¡æœ‰ç©å®¶
		log("game over");
	}
	GameScene::Win(_myplayer);
}

bool GameScene::checkCollisionWithOther(character* chara) {
	auto pos = tileCoordForPosition(chara->getPosition());
	for (auto c : _game_players) {
		if (c == chara) {
			continue;
		}
		else if (tileCoordForPosition(c->getPosition()) == pos) {
			// æ­£åœ¨ç¢°æ’
			return true;
		}
	}
	return false;
}

void GameScene::Win(character* chara) {
	//å¢åŠ éŸ³æ•ˆ
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume = UserDefault::getInstance()->getFloatForKey("effectPercent");
	audio->setEffectsVolume(volume);
	audio->playEffect("effect/win.wav", false);
	gameOver("Play Again");
}

void GameScene::Lose(character* chara) {
	//å¢åŠ éŸ³æ•ˆ
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume = UserDefault::getInstance()->getFloatForKey("effectPercent");
	audio->setEffectsVolume(volume);
	audio->playEffect("effect/lose.wav", false);
	gameOver("Game Win");
}
// æ¸¸æˆç»“æŸ
void GameScene::gameOver(std::string message) {
	// è·å¾—è®¾å¤‡å¯è§è§†å›¾å¤§å°
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto backGround = cocos2d::Sprite::create("BackGround/temple of times.png");
	backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);
	// â€œé‡æ–°å¼€å§‹â€æŒ‰é’®
	auto restart_button = Button::create("GameUI/button.png");
	restart_button->setScale(2);
	restart_button->setTitleText(message);
	restart_button->setTitleFontName("å¾®è½¯é›…é»‘");
	restart_button->setTitleFontSize(16);
	restart_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.7));
	restart_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFadeBL::create(2.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(restart_button, 1);

	// â€œè¿”å›ä¸»èœå•â€æŒ‰é’®
	auto back_button = Button::create("GameUI/button.png");
	back_button->setScale(2);
	back_button->setTitleText("Return Menu");
	back_button->setTitleFontName("å¾®è½¯é›…é»‘");
	back_button->setTitleFontSize(16);
	back_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.4));
	back_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionShrinkGrow::create(2.0, OpenScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(back_button, 1);
}
>>>>>>> ee7bee9103b469410e00c25c26b131689eb03efb
