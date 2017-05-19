#ifndef GameTheme_hpp
#define GameTheme_hpp

#include "cocos2d.h"
#include "Character.h"
#include "Bubbles.h"
#include <array>

class GameScene : public cocos2d::Layer
{
public:
    using tilePosition = cocos2d::Vec2;
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void setViewPointCenter(cocos2d::Vec2 position);
    
    void addCloseMenu();
    void addOthersPlayers();        // 增加其他玩家
    
    void myKeyboardOnL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void myKeyboardOffL(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    // 需要不停移动的...
    // 注意补充下动画逻辑
    void mySpriteMove();
    
    void update(float dt) override;
    /*********碰撞检测*************/
    // 检测人物移动是否可以进行，碰撞检测
    bool accessAble(cocos2d::Vec2);
    // 把坐标变更为tilemap的坐标
    cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 PositionForTileCoord(cocos2d::Vec2 pos);
    bool hasCollisionInGridPos(cocos2d::Vec2 pos);
    
    
    /********泡泡释放*************/
    void setBubble();
    void BubbleBoom(Ref* sender);
    Bubbles* hasBubble(cocos2d::Vec2 tilePos);
private:
    // SIZE OF SCREEN
    cocos2d::Size visibleSize;
    float offx;
    float offy;
    
    // 获取动画
    cocos2d::Animation* getAnimationByName(std::string animName,float delay,int animNum);
    
    
    /***** tilemap的大小变化率 TODO:可以放到配置文件 *****/
    cocos2d::TMXTiledMap *_tileMap;
    cocos2d::TMXLayer *_background;
    cocos2d::TMXObjectGroup *objects;
    cocos2d::TMXLayer *_meta;
    
    /**** player的属性, 和自己的player的属性, 可以考虑fsm和vector ****/
    character* _myplayer;
    
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
    
    bool check_chain_boom(cocos2d::Vec2 pos);
    // 爆炸，受下方两种爆炸方式调用
    void boom_animate(cocos2d::Vec2 pos, int power, int vector);
    void horizontal_boom(cocos2d::Vec2 pos, int power);
    void vertival_boom(cocos2d::Vec2 pos, int power);
    void add_and_clear_with_time(cocos2d::Sprite* sp, float dt, cocos2d::Vec2 pos);
    void spriteMoveFinished(cocos2d::Object* psender);
};

#endif /* GameTheme_hpp */
