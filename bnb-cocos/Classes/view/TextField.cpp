﻿#include "TextField.h"
using namespace ui;

Layer* TextFieldTest::getTextField() {
	return dynamic_cast<Layer*>(Players::getCurrent()->getChildByName("TextField"));
}
bool TextFieldTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 添加一个Text，用于显示文本框事件类型
	_displayValueLabel = Text::create("Please Touch the textfield", "微软雅黑", 32);
<<<<<<< HEAD
	_displayValueLabel->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.6));
=======
	_displayValueLabel->setPosition(Vec2(visibleSize.width *0.4,  visibleSize.height*0.6));
>>>>>>> WebGameLogic
	this->addChild(_displayValueLabel);
	// 添加一个Text，当数据输入结束时，显示输入的数据
	_messageValueLabel = Text::create("you Don't input any data", "微软雅黑", 32);
	_messageValueLabel->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.5));
	this->addChild(_messageValueLabel);

	// 创建文本框
	textField = TextField::create("Please input your NAME", "Arial", 32);
	textField->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height *0.4));
	
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(TextFieldTest::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
	// 添加文本框事件监听器
	textField->addEventListener([=](Ref *pSender, TextField::EventType type) {
		// 根据文本框的事件类型执行相应的代码
		//this->setKeypadEnabled(true);
		
		switch (type)
		{
		case TextField::EventType::ATTACH_WITH_IME:
			_displayValueLabel->setString("input beggin");
			break;
		//case TextField::EventType::DETACH_WITH_IME:
		//{
		//	_displayValueLabel->setString("input finished");
		//	// 获得文本框输入的数据
		//	std::string value = textField->getStringValue();
		//	// 如果数据大于0，显示在_messageValueLabel当中
		//	if (value.length() > 0)
		//	{
		//		_messageValueLabel->setString("your name:" + value);
		//		textField->setString("          ");
		//	}
		//	else
		//	{
		//		_messageValueLabel->setString("you Don't input any data!");
		//	}
		//}
		//break;
		case TextField::EventType::INSERT_TEXT:
			_displayValueLabel->setString("insert data");
			break;
		case TextField::EventType::DELETE_BACKWARD:
			_displayValueLabel->setString("delete data");
			break;
		default:
			break;
		}

	});
	this->addChild(textField);
	return true;
}
void TextFieldTest::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event*event) {
	log("text was called");
	if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
	{
		log("回车 was called");
		_displayValueLabel->setString("input finished");
		// 获得文本框输入的数据
		std::string value = textField->getStringValue();
		// 如果数据大于0，显示在_messageValueLabel当中
		if (value.length() > 0)
		{
			_messageValueLabel->setString("your name:" + value);
			textField->setString("          ");
		}
		else
		{
			_messageValueLabel->setString("you Don't input any data!");
		}
	}
}