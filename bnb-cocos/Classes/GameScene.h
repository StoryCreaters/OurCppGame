#ifndef GameTheme_hpp
#define GameTheme_hpp

#include "cocos2d.h"
#include "Character.h"
#include "Bubbles.h"
#include <array>

class GameScene : public cocos2d::Layer
{
public:
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
    
    /********泡泡释放*************/
    void setBubble();
    void BubbleBoom(Ref* sender);
private:
    // 获取动画
    cocos2d::Animation* getAnimationByName(std::string animName,float delay,int animNum);
    
    /***** tilemap的大小变化率 TODO:可以放到配置文件 *****/
    cocos2d::TMXTiledMap *_tileMap;
    cocos2d::TMXLayer *_background;
    cocos2d::TMXObjectGroup *objects;
    cocos2d::TMXLayer *_meta;
    
    /**** player的属性, 和自己的player的属性, 可以考虑fsm和vector ****/
    character* _myplayer;
    cocos2d::Vector<Bubbles*> _screen_bubbles;                  // 保存玩家的泡泡, 用来检测碰撞
//    cocos2d::Vector<character*> _players;        //保存玩家的容器
//    std::vector<cocos2d::Vec2> _bubbles;        // 保存玩家释放的bubble
    int _my_bubbles;
    
    // 临时纠错值, y坐标还有坑呜呜呜
    float tmp_y = 0.1;
    
    // 表示自己运动状况的量, true就开始运动, 共有四个方向
    enum _optionCode {
        GO_UP, GO_DOWN, GO_LEFT, GO_RIGHT, DEFAULT
    } _direction;
    std::array<bool, 4> _my_sprite_move;
};

#endif /* GameTheme_hpp */
