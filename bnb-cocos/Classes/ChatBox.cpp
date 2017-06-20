#include "ChatBox.h"
using namespace ui;

extern std::string Msg;

bool ChatBox::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
	
	
    addTextField();

    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChatBox::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);


	this->schedule(schedule_selector(ChatBox::update));

    return true;
}

void ChatBox::addTextField() {
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
    writeText = ui::TextField::create("Please input chat message", "fonts/GloriaHallelujah.ttf", 40);
    writeText->setColor(Color3B::BLACK);
    writeText->setPosition(Vec2(visibleSize.width / 2 , 150));
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChatBox::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    addChild(writeText);

}

void ChatBox::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event*event) {
    if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        cur_msg = writeText->getString();
        if (!cur_msg.empty()) {
            writeText->setString("");
            addChatLine(cur_msg);
        }
    }
}

void ChatBox::addChatLine(const std::string s) {
//    auto label = MenuItemLabel::create(Label::create(helps[i], "fonts/GloriaHallelujah.ttf", 35));
//    label->setColor(Color3B::BLACK);
//    _menuitems.pushBack(label);

    auto content = UserDefault::getInstance()->getStringForKey("MyName") + " : " + s;
    auto label = MenuItemLabel::create(Label::create(content, "微软雅黑", 20));
    label->setColor(Color3B::WHITE);
    chatlines.pushBack(label);
    if (chatlines.size() > 10) {
        chatlines.erase(chatlines.begin());
    }

    alignChat();
}

void ChatBox::alignChat() {
	
    log("lines number:%zd", chatlines.size());
    this->removeChildByName("lines");
    auto show_menus = Menu::createWithArray(chatlines);
    show_menus->alignItemsVertically();
    show_menus->setPosition(Vec2(350, 400));
    // can we do it elegantly?
    show_menus->setName("lines");
	show_menus->setAnchorPoint(Vec2(0,0));

    addChild(show_menus);
}


void ChatBox::update(float dt)
{
	if (!Msg.empty())
		addChatLine(Msg);
	Msg.clear();
}
