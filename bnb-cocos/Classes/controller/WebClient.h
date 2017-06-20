#ifndef WebClient_hpp
#define WebClient_hpp

#include "cocos2d.h"
#include "network/WebSocket.h"
using namespace cocos2d::network;
using namespace cocos2d;

class GameScene;
class character;

class WebClient: public cocos2d::Layer, public WebSocket::Delegate //WebSocket委托
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float dt) override;
    CREATE_FUNC(WebClient);
private:
    //这些虚函数WebSocket的回调
    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);
private:
    //WebSocket实例化
    WebSocket* m_pWebSocket;
    GameScene* runningGameScene;
    character* mychara;
};

#endif /* WebClient_hpp */
