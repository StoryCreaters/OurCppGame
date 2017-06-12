#include "Vehicle.h"
#include "Settings.h"

USING_NS_CC;

bool Vehicle::initWithType(VehicleType type)
{
    switch(type)
    {
        case VehicleType::OWL:
            _name_index = "Rowl";
            break;
        // UNDO:
        case VehicleType::TUTLE:
            _name_index = "Tutle";
            break;
        default:
            log("pass value in vehicle false");
            break;
    }
    this->initWithSpriteFrameName(_name_index + "_down_01.png");
    log("create :%s", _name_index.c_str());
    this->setAnchorPoint(Vec2(-0.1, 0.25));
    return true;
}


Vehicle* Vehicle::create(VehicleType type)
{
    Vehicle* vehicle = new Vehicle();
    if(vehicle && vehicle->initWithType(type))
    {
        vehicle->autorelease();
        return vehicle;
    }
    else
    {
        delete vehicle;
        vehicle = NULL;
        return NULL;
    }
}

void Vehicle::changeTo(int direction) {
    log("veh dir:%d", direction);
    log("name index: %s", this->_name_index.c_str());
    std::string next_direction(_name_index + "_"+ std::string(settings::GameScene::direc_string[direction]) +"_");
    log("%s", next_direction.c_str());
    auto tmp_f = SpriteFrameCache::getInstance()->getSpriteFrameByName(next_direction + "01.png");
    setSpriteFrame(tmp_f);
}
