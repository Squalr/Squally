#pragma once
#include "cocos2d.h"

#include "Engine/GlobalNode.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class Input : public GlobalNode
{
public:
	static void registerGlobalNode();

	static bool isKeyJustPressed(EventKeyboard::KeyCode keyCode);
	static bool isPressed(EventKeyboard::KeyCode keyCode);
	static bool isReleased(EventKeyboard::KeyCode keyCode);

private:
	Input();
	~Input();

	static Input* getInstance();
	void initializeListeners() override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	std::unordered_map<int, bool> pressedKeysPrevious;
	std::unordered_map<int, bool> pressedKeys;

	static Input * instance;
};
