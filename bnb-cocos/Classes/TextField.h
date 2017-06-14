#pragma once
#ifndef __UITest__TextFieldTest__
#define __UITest__TextFieldTest__

#include <iostream>
#include "cocos2d.h"
#include "view/CharacterSelect.h"
#include "ui/CocosGUI.h"

class TextFieldTest : public Layer 
{
protected:
	// 定义Text，用于显示文本框事件类型
	cocos2d::ui::Text* _displayValueLabel;
	cocos2d::ui::Text* _messageValueLabel;
public:
	virtual bool init();
	static Layer* getTextField();
	/**
	* 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
	*/
	CREATE_FUNC(TextFieldTest);

};


#endif /* defined(__UITest__TextFieldTest__) */