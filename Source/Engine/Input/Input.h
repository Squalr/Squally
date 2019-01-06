#pragma once
#include <unordered_map>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Event;
}

class Input : public GlobalNode
{
public:
	static void registerGlobalNode();

	static cocos2d::EventKeyboard::KeyCode getActiveModifiers();
	static bool isKeyJustPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	static bool isKeyJustReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	static bool isPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	static bool isReleased(cocos2d::EventKeyboard::KeyCode keyCode);

private:
	typedef GlobalNode super;
	Input();
	virtual ~Input();

	static Input* getInstance();
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	std::unordered_map<int, bool> pressedKeysPrevious;
	std::unordered_map<int, bool> pressedKeys;

	static Input* instance;
};
