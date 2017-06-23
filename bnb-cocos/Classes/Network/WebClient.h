/*
 单例的webclient类
 处理网络连接的逻辑
 */

#ifndef WebClient_hpp
#define WebClient_hpp

#include "network/WebSocket.h"
#include "MessageDispatcher.h"
#include <functional>
#include <map>

using namespace cocos2d::network;
using namespace cocos2d;

class GameScene;
class character;
class MessageDispatcher;



class WebClient:public WebSocket::Delegate //WebSocket委托
{
public:
    // 状态表示 & 此时状态
    enum GameStates {
        LOGIN_SCENE = 0,
        ROOM_SELECT,
        CHARACTER_SELECT,
        ONGAME
    } cur_state;
    
    // 根据传入的字符串发送信息
    void send_data(const std::string& s);
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
    
    virtual bool init();
    /*** 单例模式实现 ***/
    static WebClient* getInstance();
private:
    // 发送信息的map
    const static std::map<GameStates, std::function<std::string(const std::string)>> send_func_map;
    const static std::map<GameStates, std::function<std::string(const std::string)>> recv_func_map;
    //这些虚函数WebSocket的回调
    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);
    
    void dispatchMessage();
    WebClient();
private:
    WebClient(const WebClient&) = delete;
    WebClient& operator=(const WebClient&) = delete;
private:
    //WebSocket实例化
    WebSocket* m_pWebSocket;
};

#endif /* WebClient_hpp */
