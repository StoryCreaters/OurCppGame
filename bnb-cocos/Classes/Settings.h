#ifndef Settings_h
#define Settings_h

namespace settings {
    // 人物属性设定
    namespace Character {
        // 人物的x, y
        constexpr float character_x[] = {46, 44, 54};
        constexpr float character_y[] = {57, 56, 62};
        
        // 人物基础属性
        constexpr int start_bubbles[] = {2, 1, 2};
        constexpr int start_powers[] = {1, 2, 1};
        constexpr int start_velocity[] = {2, 1, 1};
        // 人物的max属性
        constexpr int max_bubbles[] = {7, 6, 6};
        constexpr int max_powers[] = {6, 6, 6};
        constexpr int max_velocity[] = {6, 7, 5};
        
        // 人物运动动画帧数
        constexpr int animation_frames[] = {4, 6, 6};
        // 人物的数量
        constexpr unsigned character_nums = sizeof(start_powers) / sizeof(int);
        
        // 人物对应名称/ 路径
        constexpr char *sprite_paths[] = {
            "GamePlayer/player1.png",
            "GamePlayer/player2.png",
            "GamePlayer/player3.png"
        };
        // 精灵的名称
        constexpr char *sprite_names[] = {"player1", "player2", "player3"};
        
    }
    
    namespace GameScene {
        // 瓦片地图大小变化率
        constexpr float _tile_delta_rate = 1.15f;
        
        // animation 相关
        constexpr int bubble_frame_nums = 3;
        
        constexpr char* background_music = "music/MEGALOVANIA.mp3";
        
        constexpr char* direc_string[] = {"up", "down", "left", "right"};
    }
    
    namespace PreLoadScene {
        // 基础道具动画
        constexpr char* gifts_animation = "PropResource/PropGifts.plist";
        // 人物
        constexpr char* person_animation[] = {"GamePlayer/player1_animation/player1.plist", "GamePlayer/player2_animation/player2.plist"};
        // bubbles
        constexpr char* bubbles_animation = "BubbleImages/images/stable/bubble_bump.plist";
        
        constexpr char* to_load_music = "music/Temple of Time.mp3";
        
        constexpr int delayFrame = 100;
        constexpr float delaytime = 0.5f;
    }
    
    namespace Bubbles {
        constexpr char* bubbles_file = "BubbleImages/images/stable/Popo_01.png";
    }
}

#endif /* Settings_h */
