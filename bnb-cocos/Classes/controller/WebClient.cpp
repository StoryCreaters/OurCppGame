#include "WebClient.h"
#include "view/GameScene.h"

bool WebClient::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    m_pWebSocket = new WebSocket();
    m_pWebSocket->init(*this, "ws://127.0.0.1:9000");
    
    auto running_scene = Director::getInstance()->getRunningScene();
    runningGameScene = dynamic_cast<GameScene*>(running_scene->getChildByTag(10));
    
    return true;
}

void WebClient::onOpen(WebSocket * ws)
{
    CCLOG("OnOpen");
}

void WebClient::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
    std::string textStr = data.bytes;
    CCLOG(textStr.c_str());
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
