// 进入gameScene前自动加载的class, 可以附上风同学的友情提示哟～
// 加载各种精灵资源/音乐资源，方便祖国和人民搞事情
#ifndef PreLoad_hpp
#define PreLoad_hpp

#include "cocos2d.h"
USING_NS_CC;

class PreLoadScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(PreLoadScene);
    
private:
    // 加载精灵帧，精灵图片(like bubble, character)
    void loadSpriteFrame();
    void loadMusic();
    void loadEffect();
    // 设置、更新进度条
    void setProgress();
    void progressUpdate();
    
    void onEnterTransitionDidFinish() override;
    void update(float dt) override;
protected:
    // 用来保存游戏需要加载的资源总数
    int _sourceCount;
    // 进度条
    ProgressTimer* _progress;
    // 进度条更新的次数
    float _progressInterval;
};


#endif /* PreLoad_hpp */
