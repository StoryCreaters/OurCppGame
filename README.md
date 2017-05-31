# OurCppGame
cocos2d cpp game(bnb)

BnbGameServer 是服务端（已提交）
BnbGameClient 是客户端（正在测试，未提交）

WebGameScene是联机对战的场景
它继承GameScene（可能需要适当调整GameScene）
GameServer GameClient 都作为WebGameScene的数据成员。（GameClient建立指针数组也行，或者用vector）


实现的大致思路
在WebGameScene的init中，先GameScene::init()
然后初始化GameServer（建立套接字、bind、listen），让它监听

（为了简单起见，先默认人数为2)

接着调用addPlayer()函数
在该函数里面，初始化一个GameClient（建立套接字、connect）
然后调用GameServer::ProcessGameServer()  (accept、creatThread)
此时，GameClient就会连接成功。
之后是通过线程传输数据(unfinished)
