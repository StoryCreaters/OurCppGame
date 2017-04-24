#ifndef GameTheme_hpp
#define GameTheme_hpp

#include "cocos2d.h"
#include "Character.h"
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
    bool accessAble(cocos2d::Vec2);
    cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 pos);
private:
    float _deltaRate;
    cocos2d::TMXTiledMap *_tileMap;
    cocos2d::TMXLayer *_background;
    cocos2d::TMXObjectGroup *objects;
    cocos2d::TMXLayer *_meta;
    
    character* _myplayer;
    cocos2d::Vector<character*> _players;        //保存玩家的容器
    
    // 表示自己运动状况的量, true就开始运动
    enum _optionCode {
        GO_UP, GO_DOWN, GO_LEFT, GO_RIGHT
    };
    std::array<bool, 4> _my_sprite_move;
    
};

#endif /* GameTheme_hpp */
