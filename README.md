# OurCppGame
cocos2d cpp game(bnb)</br>

BnbGameServer 是服务端（已提交）</br>
独立，小黑框运行，负责接收并发送数据（已实现）</br>
多个客户端连接服务端，超过额定数目会拒绝连接（已实现）</br>
地图需要放进去（未实现）</br></br>

BnbGameClient 是客户端（已提交）</br>
在游戏本体中，作为WebGameScene一个数据成员</br>

WebGameScene场景</br>
继承GameScene</br>
需要重构几个继承的函数</br>

目前仍有一个最最最魔性的BUG。</br>
明天要考高数了，不写了复习去</br>

<<<<<<< HEAD
- character: 显示玩家的类，需要有不同的基本三维和max的三维，还有对应的图片和动画
- bubble : 水泡类，需要管理自身的火力，由于不知道爆炸的运行机制，这里暂时不讨论
- Monsters : 目前没有写但是可以补充的class , 对应怪物和AI(笑)？
- GameItem: 游戏的道具，这里组合出三种...要不要考虑用继承(笑)？请先实现这三种吧

## GUI

#### 图形界面, 资源请放在GameUI目录下

- helloworld Scene: 这是自动生成的，在这里没有用处，但是我们能把它当作一个可以抄的demo
- SwallowTouch: 屏蔽下层事件响应的layer
- OpenScene: 开场，注意其他的scene争取回到这里
- toStart: 准备开始游戏的界面
- RoomChooseScene: 在web对战中，选择房间的
- PauseWithLabelLayer: 提供一个Label, 并且显示所提供label的层， 用于做help提示

## GameScene

#### 游戏主界面, 需要重构

- mapscene: 地图scene
- GameScene: 游戏进行的场所

## Layer

#### 游戏的层，用于实现逻辑

## 团队人员

* mapleFU(付旭炜)
* shadowfox(钟钰琛)
* chris0(王芷怡)

## 开发流程

##### 先实现项目要求的基本功能

* 支持动画效果**(finished)**
* 支持鼠标和键盘操作交互**(finished)**
* 支持障碍物**(finished)**
* 支持泡泡的放置与爆炸**(finished)**
* 支持三种基本道具**(finished)**
* 实现服务端，支持多人在同一地图游戏
* 支持地图绘制，人物绘制，水泡效果绘制**(finished)**

##### 额外功能

* 支持多个角色**(finished)**
* 支持聊天
* 支持房间列表
* 支持>=2张地图**(finished)**
* 支持>=2种游戏模式
* 支持使用道具**(finish)**
* 支持骑宠**(finish)**


### 开发周期

* 完善基础功能，作出单机版demo
* 重构代码，用mvc, fsm等将游戏的逻辑组织好
* 跟web交互
* 完善剩余功能和网络效果


## 命名规则

class以大写开头，大写分割单词，比如**Bubbles, OpenScene**

private变量小写，以_分割，例如**my_private_var**

public小写 以_分割，例如**my_public**

函数尽量用驼峰命名法

## 注意事项

1. 想实现新的功能请在分支中写，master为稳定的版本
2. 以主要功能和队长mapleFU设计的类为首要完成目标
3. 资源信息等尽量放在settings目录下
4. 注意windows系统的编码问题
5. 有问题请发送电子邮件至maplewish117@gmail.com处
=======
>>>>>>> 92e3e854e26c5cd8b58ee13989019241d9a68e0d

