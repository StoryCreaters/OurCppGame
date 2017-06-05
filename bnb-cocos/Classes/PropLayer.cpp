#include "PropLayer.h"
#include "GameItem.h"
#include "Settings.h"
using namespace ui;
constexpr char* res[] = {
	"Gift_RspeedUp",
	"Gift_needle",
	"Gift_guard",
	"Gift_upper"
};
int i;
bool PropLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	for (i = 0; i < prop_nums; ++i) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto cur_button = Button::create(settings::PropLayer::gridBkg);
		Size buttonSize = cur_button->getContentSize();
		cur_button->addChild(Sprite::createWithSpriteFrameName(std::string(res[i]) + "_01.png"),0); 
		cur_button->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height *0.2 + i*buttonSize.height));
		LabelTTF* label;
		label = LabelTTF::create("1", "Marker Felt", 8);
		label->setPosition(cocos2d::Vec2(visibleSize.width *0.2, visibleSize.height *0.2 + i*buttonSize.height));
		cur_button->addChild(label, 1, i);
		addChild(cur_button, 2, i);
		cur_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				Changeprop(i,this);
			}
		});
	}
	return true;
}
//改变道具数量的函数
void PropLayer::Changeprop(int i, Ref *sender)
{
	auto button=(Button*)this->getChildByTag(i);
	auto scorelabel = (LabelTTF*)button->getChildByTag(i);
	auto width = scorelabel->getPosition().x;
	auto height= scorelabel->getPosition().y;
	this->removeChildByTag(i);
	LabelTTF* label = LabelTTF::create("0", "Marker Felt", 8);
	label->setPosition(cocos2d::Vec2(width, height));
	button->addChild(label, 1, i);
}