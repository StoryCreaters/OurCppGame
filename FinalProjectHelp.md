# Final Project: crazy arcade

## sprite

* character: 显示玩家的类，需要有不同的基本三维和max的三维，还有对应的图片和动画
* bubble : 水泡类，需要管理自身的火力，由于不知道爆炸的运行机制，这里暂时不讨论
* Monsters : 目前没有写但是可以补充的class , 对应怪物和AI(笑)？
* GameItem: 游戏的道具，这里组合出三种...要不要考虑用继承(笑)？请先实现这三种吧

## GUI

* helloworld Scene: 这是自动生成的，在这里没有用处，但是我们能把它当作一个可以抄的demo
* SwallowTouch: 屏蔽下层事件响应的layer
* OpenScene: 开场，注意其他的scene争取回到这里
* toStart: 准备开始游戏的界面
* RoomChooseScene: 在web对战中，选择房间的
* PauseWithLabelLayer: 提供一个Label, 并且显示所提供label的层， 用于做help提示

## GameScene

* mapscene: 地图scene
* GameScene: 游戏进行的场所

## 命名规则

class以大写开头，大写分割单词，比如**Bubbles, OpenScene**

private变量小写，以_分割，例如**\_my_private_var**

public小写 以\_分割，例如**my_public**





