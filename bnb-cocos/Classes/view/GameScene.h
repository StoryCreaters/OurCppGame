#ifndef GameTheme_hpp
#define GameTheme_hpp

#include "cocos2d.h"
#include "Settings.h"
#include <array>
#include "../model/GameItem.h"
#include <thread>
#include "../web client/WebGameScene.h"

class character;
class Bubbles;
class GameItem;
<<<<<<< .merge_file_a90984
=======

extern int RoomPlayers;
extern int whichPlayer;
>>>>>>> .merge_file_a92668

class GameScene : public cocos2d::Layer
{
public:
    friend class PlayerController;
    friend class CharStuck;
    friend class character;
	friend class GameClient;
    using tilePosition = cocos2d::Vec2;
    
    // 返回gameScene对象
    static cocos2d::Scene* createScene();
    static GameScene* getCurrentMap();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
	void addPlayer(character::characterType T, int index, bool isMyPlayer = false);

    void setViewPointCenter(cocos2d::Vec2 position);
    
    void addCloseMenu();
    void addOthersPlayers();        // 增加其他玩家
    
    void myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    // 需要不停移动的...
    // 注意补充下动画逻辑
    void mySpriteMove();
<<<<<<< .merge_file_a90984
    
=======
>>>>>>> .merge_file_a92668
    
    

	void update(float dt) override;
    /*********碰撞检测*************/
    // 检测人物移动是否可以进行，碰撞检测
    bool accessAble(cocos2d::Vec2);
    // 把坐标变更为tilemap的坐标
    cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 PositionForTileCoord(cocos2d::Vec2 pos);
    bool hasCollisionInGridPos(cocos2d::Vec2 pos);
    
    
    /** clear a character **/
    void RemoveCharacter(character* chara);
    
    /********泡泡释放*************/
    void setBubble(character* chara,Vec2 Pos);
<<<<<<< .merge_file_a90984
    void BubbleBoom(Ref* sender);
=======
	void BubbleBoom(Ref* sender);
>>>>>>> .merge_file_a92668
    Bubbles* hasCollideableBubble(cocos2d::Vec2 tilePos);
    Bubbles* hasBubble(cocos2d::Vec2 tilePos);
    
    // normal
    void checkGetItem(character* chara);         // update
    bool checkCollisionWithOther(character* chara);
    void CharacterMove(character* chara);
    
<<<<<<< .merge_file_a90984
private:
=======
	void callWeb(float dt);
	void end(float dt);
private:      

>>>>>>> .merge_file_a92668
    // SIZE OF SCREEN
    cocos2d::Size visibleSize;
    float offx;
    float offy;
    // TODO: restore controlls
    Layer* controllers[2];
    
    
    /***** tilemap的大小变化率*****/
    cocos2d::TMXTiledMap *_tileMap;
    cocos2d::TMXLayer *_background;
    cocos2d::TMXObjectGroup *objects;
    cocos2d::TMXLayer *_meta;
    void tileLoadProps();
    // 瓦片地图上的道具们
    std::array<std::array<int, 15>, 15> prop_on_map;
    std::array<std::array<bool, 15>, 15> prop_gotton;
    
    /**** player的属性, 和自己的player的属性, 可以考虑fsm和vector ****/
    character* _myplayer;
    cocos2d::Vector<character*> _game_players;
    
    int _my_bubbles;
    
    // 表示自己运动状况的量, true就开始运动, 共有四个方向
    enum _optionCode {
        GO_UP, GO_DOWN, GO_LEFT, GO_RIGHT, DEFAULT
    } _direction;
    std::array<bool, 4> _my_sprite_move;
    
    /**** 爆炸相关 ****/
    enum boom_vec {
        HORIZONTAL, VERTICAL
    };
    
    // stores positon of bubbles
    std::map<cocos2d::Vec2, Bubbles*> _map_screen_bubbles;
    // items on game scene
    std::map<cocos2d::Vec2, GameItem*> screenItems;
    
    bool check_chain_boom(cocos2d::Vec2 coordPos);
    
    
    // 爆炸，受下方两种爆炸方式调用
    void boom_animate(cocos2d::Vec2 pos, int power, int vector);
    void horizontal_boom(cocos2d::Vec2 pos, int power);
    void vertival_boom(cocos2d::Vec2 pos, int power);
    // TODO:对爆炸位置判断是否被波及
    void checkIfCharaFired(Vec2 position);
    
    /*** the function to clear the sprite */
    void add_and_clear_with_time(cocos2d::Sprite* sp, float dt, cocos2d::Vec2 pos);
    void spriteMoveFinished(cocos2d::Ref* psender);
    void spriteToClear(cocos2d::Ref* psender);
    
    
    /*** add item to the game ***/
    void addItems(cocos2d::Vec2 tiledPos, GameItem::ItemTools tool);
    
};

#endif /* GameTheme_hpp */
