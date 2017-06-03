#include "WebClient.h"
#include "../view/GameScene.h"
#include "Character.h"

static inline GameScene* getGameScene() {
    auto scene = Director::getInstance()->getRunningScene();
    return dynamic_cast<GameScene*>(scene->getChildByTag(10));
}

bool WebClient::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    m_pWebSocket = new WebSocket();
    m_pWebSocket->init(*this, "ws://127.0.0.1:9000");
    
    scheduleUpdate();
    return true;
}

void WebClient::onOpen(WebSocket * ws)
{
    CCLOG("OnOpen");
}

void WebClient::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
    std::string textStr = data.bytes;
    log(textStr.c_str());
}

void WebClient::onClose(WebSocket * ws)
{
    if (ws == m_pWebSocket)
    {
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

void WebClient::update(float dt) {
    if (!runningGameScene) {
        runningGameScene = getGameScene();
        if (runningGameScene == nullptr) {
            return;
        } else {
            mychara = dynamic_cast<character*>(runningGameScene->getChildByTag(20));
        }
    }
    char my_direct[2];
    int i;
    for (i = 0; i < 4; ++i) {
        if (mychara->_chara_move[i])
            break;
    }
    if (i == 4) return;
    
    sprintf(my_direct, "%d", i);
    log(my_direct);
    m_pWebSocket->send(my_direct);
}
