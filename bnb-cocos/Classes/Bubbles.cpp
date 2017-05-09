#include "Bubbles.h"
#include "Settings.h"

bool Bubbles::initWithPower(int power) {
    using namespace settings::Bubbles;
    this->_power = power;
    this->initWithFile(bubbles_file);
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
