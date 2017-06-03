#ifndef CommonUse_hpp
#define CommonUse_hpp

#include "cocos2d.h"
cocos2d::Animation* getAnimationByName(const std::string &animName,float delay,int animNum);
void runAnimationByName(cocos2d::Sprite* spr,const std::string &animName,float delay,int animNum);


#endif /* CommonUse_hpp */
