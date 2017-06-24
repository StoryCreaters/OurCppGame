#include "ChatBox.h"
#include "WebClient.h"
using namespace ui;
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
    
    return true;
    
    
}

ChatBox* ChatBox::getChatBox() {
    auto layer = Director::getInstance()->getRunningScene()->getChildByName("CharacterSelect");
    auto item = layer->getChildByName("ChatBox");
    assert(item);
    return dynamic_cast<ChatBox*>(item);
}

void ChatBox::addTextField() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    writeText = ui::TextField::create("Please input chat message", "fonts/GloriaHallelujah.ttf", 40);
    writeText->setColor(Color3B::GRAY);
    writeText->setPosition(Vec2(visibleSize.width / 2 , 150));
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChatBox::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    addChild(writeText);
}

void ChatBox::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event*event) {
    if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        auto cur_msg = writeText->getString();
        if (!cur_msg.empty()) {
            writeText->setString("");
            WebClient::getInstance()->send_data("Chat " + cur_msg);
        }
    }
}

void ChatBox::addChatLine(const std::string& s) {
//    auto label = MenuItemLabel::create(Label::create(helps[i], "fonts/GloriaHallelujah.ttf", 35));
//    label->setColor(Color3B::BLACK);
//    _menuitems.pushBack(label);
    auto content = UserDefault::getInstance()->getStringForKey("MyName") + " : " + s;
    auto label = MenuItemLabel::create(Label::create(content, "fonts/IndieFlower.ttf", 20));
    label->setColor(Color3B::BLACK);
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
    show_menus->setPosition(Vec2(200, 400));
    // can we do it elegantly?
    show_menus->setName("lines");
    addChild(show_menus);
}

void ChatBox::addChatLine(const std::string& name, const std::string &s) {
    auto content = name + " : " + s;
    auto label = MenuItemLabel::create(Label::create(content, "fonts/IndieFlower.ttf", 20));
    label->setColor(Color3B::BLACK);
    chatlines.pushBack(label);
    if (chatlines.size() > 10) {
        chatlines.erase(chatlines.begin());
    }
    alignChat();
}
