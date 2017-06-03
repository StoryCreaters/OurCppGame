#include "CommonUse.h"
/*** 从aniName 和delay 得到 播放的动画, 动画从01开始 ***/
cocos2d::Animation* getAnimationByName(std::string animName,float delay,int animNum){
    using namespace cocos2d;
    auto animation = Animation::create();
    // 循环从精灵帧缓存中获取与图片名称相对应的精灵帧组成动画
    for(unsigned int i = 1;i<animNum;i++){
        // 获取动画图片名称，例如plane0.png
        std::string frameName = animName;
        frameName.append(StringUtils::format("%02d",i)).append(".png");
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName.c_str()));
    }
    // 设置动画播放的属性
    animation->setDelayPerUnit(delay);
    // 让精灵对象在动画执行完后恢复到最初状态
    animation->setRestoreOriginalFrame(true);
    // 返回动画对象
    return animation;
}

void runAnimationByName(cocos2d::Sprite* spr,std::string animName,float delay,int animNum) {
    auto anime = getAnimationByName(animName, delay, animNum);
    auto animate = cocos2d::Animate::create(anime);
    auto player_anime = cocos2d::RepeatForever::create(animate);
    spr->runAction(player_anime);
}

