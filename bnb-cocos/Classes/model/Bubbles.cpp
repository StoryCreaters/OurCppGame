#include "Bubbles.h"
#include "Settings.h"
#include "Character.h"

bool Bubbles::initWithPower(int power, character* chara) {
    using namespace settings::Bubbles;
    this->setterCharacter = chara;
    this->_power = power;
    this->initWithFile(bubbles_file);
    return true;
}

Bubbles* Bubbles::create(int power, character* setter) {
    auto *bubble = new Bubbles();
    if (bubble && bubble->initWithPower(power, setter)) {
        bubble->autorelease();
        return bubble;
    } else {
        delete bubble;
        bubble = nullptr;
        return nullptr;
    }
}

