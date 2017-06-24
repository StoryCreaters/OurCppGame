#include "WebClient.h"
#include "../view/GameScene.h"
#include "Character.h"
#include "Settings.h"
#include "MessageRecvDispatcher.h"

const std::map<WebClient::GameStates, std::function<std::string(const std::string)>>
WebClient::send_func_map = {
    {WebClient::LOGIN_SCENE, MessageDispatcher::Login},
    {WebClient::ROOM_SELECT, MessageDispatcher::RoomSelect},
    {WebClient::CHARACTER_SELECT, MessageDispatcher::CharSelect},
    {WebClient::ONGAME, MessageDispatcher::OnGame}
};

const std::map<WebClient::GameStates, std::function<std::string(const std::string)>>
WebClient::recv_func_map = {
    {WebClient::LOGIN_SCENE, MessageRecvDispatcher::Login},
    {WebClient::ROOM_SELECT, MessageRecvDispatcher::RoomSelect},
    {WebClient::CHARACTER_SELECT, MessageRecvDispatcher::CharSelect},
    {WebClient::ONGAME, MessageRecvDispatcher::OnGame}
};

WebClient::WebClient() {
    this->init();
}

static inline GameScene* getGameScene() {
    auto scene = Director::getInstance()->getRunningScene();
    return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}

bool WebClient::init() {
    m_pWebSocket = new WebSocket();
    m_pWebSocket->init(*this, settings::WebClient::ws_url);
    if (m_pWebSocket == nullptr) {
        CC_SAFE_DELETE(m_pWebSocket);
    }
    cur_state = LOGIN_SCENE;
    return true;
}

void WebClient::onOpen(WebSocket * ws)
{
    CCLOG("OnOpen");
}

void WebClient::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
    
    
    auto length = data.len;
    std::string textStr = data.bytes;
    textStr = textStr.substr(0, length);
    log("recv %s", textStr.c_str());
    auto func = recv_func_map.at(cur_state);
    func(textStr);
}

void WebClient::onClose(WebSocket * ws)
{
    
    if (ws == m_pWebSocket)
    {
        ws->send("close");
        m_pWebSocket = NULL;
    }
    CC_SAFE_DELETE(ws);
    CCLOG("onClose");
}

void WebClient::onError(WebSocket * ws, const WebSocket::ErrorCode & error)
{
    if (ws == m_pWebSocket)
    {
        char buf[100] = { 0 };
        sprintf(buf, "an error was fired, code: %d", error);
    }
    CCLOG("Error was fired, error code: %d", error);
}

WebClient* WebClient::getInstance() {
    static WebClient webclient;
    return &webclient;
}

void WebClient::send_data(const std::string& s) {
    auto str_func = send_func_map.at(cur_state);
    log("state %d", cur_state);
    m_pWebSocket->send(str_func(s));
}

