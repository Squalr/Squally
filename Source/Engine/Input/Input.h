#pragma once
#include <unordered_map>

#include "cocos/base/CCInputEvents.h"

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Event;
}

class Input : public GlobalNode
{
public:
	static void registerGlobalNode();

	static cocos2d::InputEvents::KeyCode GetActiveModifiers();
	static bool IsPressed(cocos2d::InputEvents::KeyCode keyCode);
	static bool IsReleased(cocos2d::InputEvents::KeyCode keyCode);

protected:
	Input();
	virtual ~Input();

	void initializeListeners() override;

private:
	typedef GlobalNode super;

	static Input* GetInstance();

	void onKeyPressed(cocos2d::InputEvents::KeyCode keyCode);
	void onKeyReleased(cocos2d::InputEvents::KeyCode keyCode);
	
	static cocos2d::InputEvents::MouseEventArgs MouseState;
	static std::unordered_map<int, bool> PressedKeysPrevious;
	static std::unordered_map<int, bool> PressedKeys;

	static Input* Instance;
};
