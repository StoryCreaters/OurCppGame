﻿#pragma once
#ifndef PropLayer_hpp
#define PropLayer_hpp

// the scene to show the props we can use
// we have
#include "cocos2d.h"
#include <array>
#include "ui/CocosGUI.h"
USING_NS_CC;

class GameItem;
class character;

class PropLayer : public cocos2d::Layer
{
public:
    friend class PropItem;
    friend class GameItem;
    friend class PropController;
    // 道具相关的枚举
    enum PropType {
        ALLPOWER, NEEDLE, RSPEED, GUARD
    };
    static constexpr int prop_nums = 4;
    std::function<void(void)> getPropfuncs(int index);
    std::function<bool(void)> getAblefuncs(int index);
    static Layer* getPropLayer();
    
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(PropLayer);
    // 得到道具
    void addProp(PropType T);
    // 使用道具 需要re align
    void UseProp(int num, character* chara);
    //改变道具上的数字
    void propPlus(int, Ref *sender);
    void propMinus(int, Ref *sender);
    // 判断道具是否可用
    bool isUseable(int index) {
        return currentProps[index];}
private:
    // 根据myProps重写道具数目，改变string
    void AlignProps();
    // to store and show the Items
//    std::vector<int> currentProps(4,0);
    std::array<int, prop_nums> currentProps;
    cocos2d::Vector<cocos2d::ui::Button*> show_buttons;
    void addProp(int index);
    void useProp(int index);
};

#endif /* PropLayer_hpp */
