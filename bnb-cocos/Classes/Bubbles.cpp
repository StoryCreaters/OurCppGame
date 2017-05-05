#include "Bubbles.h"

bool Bubbles::initWithPower(int power) {
    this->_power = power;
    this->initWithFile("GamePlayer/bubble0.png");
    return true;
}

Bubbles* Bubbles::create(int power) {
    auto *bubble = new Bubbles();
    if (bubble && bubble->initWithPower(power)) {
        bubble->autorelease();
        return bubble;
    } else {
        delete bubble;
        bubble = nullptr;
        return nullptr;
    }
}
