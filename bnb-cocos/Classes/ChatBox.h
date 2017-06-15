#ifndef ChatBox_hpp
#define ChatBox_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ChatBox : public Layer {
public:
    virtual bool init();
    ui::TextField* writeText;
    // 根据chatLines 排列
    void alignChat();
    CREATE_FUNC(ChatBox);
    void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event*event);
private:
    Vector<cocos2d::MenuItem*> chatlines;       // 对话数目
    void addTextField();
    void addChatLine(const std::string& s);
};
#endif /* ChatBox_hpp */
