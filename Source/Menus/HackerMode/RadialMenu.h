#pragma once
#include <functional>
#include "cocos/math/Vec2.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
	class LayerColor;
}

class CodeEditor;
class HackableObject;
class MenuSprite;

class RadialMenu : public SmartNode
{
public:
	static RadialMenu* create(std::function<void()> onCloseCallback);

private:
	RadialMenu(std::function<void()> onCloseCallback);
	~RadialMenu();

	void initializePositions();
	void initializeListeners();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onHackableEdit(cocos2d::EventCustom* eventArgs);
	void onHackableAttributeClick(MenuSprite* menuSprite);
	void onClose(MenuSprite* menuSprite);
	void close();

	cocos2d::Node* createRadialNode(std::string iconResource, cocos2d::Vec2 nodePosition, cocos2d::Color4F color, std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> callback, int tag);

	CodeEditor* codeEditor;
	HackableObject* activeHackableObject;

	cocos2d::LayerColor* layerColor;
	cocos2d::Node* radialMenuItems;

	std::function<void()> onRadialMenuCloseCallback;

	static const float radialMenuRadius;
	static const float lineWidth;
	static const cocos2d::Color4F dataColor;
	static const cocos2d::Color4F codeColor;
	static const float iconRadius;
};
