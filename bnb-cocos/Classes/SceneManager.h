/*
 Management of the scene
 and related to webclient(change the state for it)
 */

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "cocos2d.h"
class SceneManager {
public:
    static void toGameScene();
    static void toLoginScene();
    static void toCharaSelect();
    static void toRoomSelect();
};

#endif /* SceneManager_hpp */
