#ifndef PropLayer_hpp
#define PropLayer_hpp

// the scene to show the props we can use
// we have
#include "cocos2d.h"

USING_NS_CC;

class GameItem;
class character;

class PropLayer : public cocos2d::Layer
{
public:
    // 道具相关的枚举
    enum PropType {
        
    };
    
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PropLayer);
    // 判断道具是否已满
    bool isFull() { return (myProps.size() == 3);}
    // 得到道具
    void addProp(GameItem*);
    // 使用道具 需要re align
    void UseProp(int num, character* chara);
private:
    // 根据myProps排列道具，改变对象
    void AlignProps();
    // to store and show the Items
    Vector<GameItem*> myProps;
    Menu* shownProps;
};

#endif /* PropLayer_hpp */
