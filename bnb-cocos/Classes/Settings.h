#ifndef Settings_h
#define Settings_h

#include <string>

namespace settings {
	enum directions {
		UP, DOWN, LEFT, RIGHT, DEFAULT
	};

	namespace OpenScene {
		constexpr char* UiNames[] = {
			"GameUI/ProjectName",
			"GameUI/PlayMyself",
			"GameUI/PlayOnInternet",
			"GameUI/Settings",
			"GameUI/Help",
			"GameUI/Quit"
		};

		constexpr char* helps[] = {
			"Hi, this is a bnb game",
			"made by maplewind, Chris and shadowfox",
			"use up\\down\\left\\right to control your charactor",
			"and you can press \"help\" to get some information",
			"have fun~"
		};
	}
	// 人物属性设定
	namespace Character {
		// 与delta_rate(1.15) 相关， 考虑修改
		constexpr float grid_size = 40 * 1.15;
		constexpr float little_grid_size = 36;

		// 人物的x, y
		constexpr float character_x[] = { 46, 44, 54 };
		constexpr float character_y[] = { 57, 56, 62 };

		// 人物基础属性
		constexpr int start_bubbles[] = { 2, 1, 2 };
		constexpr int start_powers[] = { 1, 2, 1 };
		constexpr int start_velocity[] = { 2, 1, 1 };
		// 人物的max属性
		constexpr int max_bubbles[] = { 7, 6, 6 };
		constexpr int max_powers[] = { 6, 6, 6 };
		constexpr int max_velocity[] = { 6, 7, 5 };

		// 人物运动动画帧数
		constexpr int animation_frames[] = { 4, 6, 6 };
		// 人物的数量
		constexpr unsigned character_nums = sizeof(start_powers) / sizeof(int);

		// 人物对应名称/ 路径
		constexpr char *sprite_paths[] = {
			"GamePlayer/player1.png",
			"GamePlayer/player2.png",
			"GamePlayer/player3.png"
		};
		// 精灵的名称
		constexpr char *sprite_names[] = { "player1", "player2", "player3" };

	}

	namespace GameScene {
		constexpr float boom_time = 0.5f;
		// 瓦片地图大小变化率
		constexpr float _tile_delta_rate = 1.15f;

		constexpr char* backGroundPicture[] = { "BackGround/Cool_background.jpg","BackGround/Character_Select.png",
			"BackGround/Gray World.jpg","BackGround/selecting_background" };

		// animation 相关
		constexpr int bubble_frame_nums = 3;

		constexpr char* background_music = "music/MEGALOVANIA.mp3";

		constexpr char* direc_string[] = { "up", "down", "left", "right" };

		// 碰撞格子大小
		//        constexpr int grid_size = 40;

		/****爆炸图片****/
		constexpr char* boom_v = "BubbleImages/images/vertical_demo.png";        // 水平爆炸
		constexpr char* boom_h = "BubbleImages/images/horizontal_demo.png";        // 竖直爆炸
		constexpr char* center_boom = "BubbleImages/images/center_demo.png";

		constexpr char* boom_anime[] = {
			"BubbleImages/images/horizontal_demo.png",
			"BubbleImages/images/vertical_demo.png"
		};
	}

	namespace PreLoadScene {
		// 基础道具动画
		constexpr char* gifts_animation[] = {
			"PropResource/PropGifts.plist"
		};
		// 人物
		constexpr char* person_animation[] = {
			"GamePlayer/player1_animation/player1.plist",
			"GamePlayer/player2_animation/player2.plist",

			"GamePlayer/CharaStucked.plist"
		};
		//四个道具item
		constexpr char* items_animation[] = {
			"PropResource/PropItems.plist"
		};
		// bubbles
		constexpr char* bubbles_animation = "BubbleImages/images/stable/bubble_bump.plist";

		constexpr char* to_load_music[] = { "music/Temple of Time.mp3","music/MEGALOVANIA.mp3","music/When The Morning Comes.mp3" };
		constexpr char* load_effect[] = { "effect/explore.wav","effect/get.wav","effect/win.wav","effect/lose.wav" };

		constexpr int delayFrame = 160;
		constexpr float delaytime = 0.5f;
	}

	namespace Bubbles {
		constexpr char* bubbles_file = "BubbleImages/images/stable/Popo_01.png";
	}

	namespace SettingScene {
		//temporary empty
	}

	namespace PropLayer {
		constexpr char* gridBkg = "riding/PropBkg.jpg";
	}

	namespace Items {
		// items and it resources
		enum ItemTools {
			POPO, POWER, RUN
		};
		// frame里面 不需要路径
		constexpr char* ItemNames[] = {
			"GiftPoPo",
			"GiftPower",
			"GiftRun"
		};
	}

	namespace FSM {

	}
}

#endif /* Settings_h */
