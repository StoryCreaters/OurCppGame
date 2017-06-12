#ifndef Vehicle_hpp
#define Vehicle_hpp

#include "cocos2d.h"

class Vehicle: public cocos2d::Sprite {
public:
    enum VehicleType {
        OWL, TUTLE
    };
    
    // 根据type 初始化骑宠
    bool initWithType(VehicleType T);
    static Vehicle* create(VehicleType T);
    // 变更方向
    void changeTo(int direction);
    void removeV() { this->removeFromParent();}
private:
    // 宠物名称索引
    std::string _name_index;
};

#endif /* Vehicle_hpp */
