#ifndef Settings_h
#define Settings_h

namespace settings {
    // 人物属性设定
    namespace Character_settings {
        
        // 人物基础属性
        constexpr int start_bubbles[] = {1, 1, 2};
        constexpr int start_powers[] = {};
        constexpr int start_velocity[] = {2, 1, 1};
        // 人物的max属性
        constexpr int max_bubbles[] = {7, 6, 6};
        constexpr int max_powers[] = {6, 6, 6};
        constexpr int max_velocity[] = {6, 7, 5};
        // 人物的数量
        constexpr unsigned character_nums = sizeof(start_powers) / sizeof(int);
        
        // 人物对应名称/ 路径
        constexpr char *sprite_paths[] = {
            "GamePlayer/player1.png",
            "GamePlayer/player2.png",
            "GamePlayer/player3.png"
        };
    }
    
    namespace GameScene_settings {
        // 瓦片地图大小变化率
        constexpr float _tile_delta_rate = 1.15;
    }
}

#endif /* Settings_h */
