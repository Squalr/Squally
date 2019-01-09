#pragma once
#include <functional>
#include "cocos/math/Vec2.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class CodeEditor;
class HackableCode;
class HackableData;
class HackableObject;
class LocalizedString;

class RadialMenu : public SmartNode
{
public:
	static RadialMenu* create(std::function<void()> onCloseCallback);

private:
	typedef SmartNode super;
	RadialMenu(std::function<void()> onCloseCallback);
	~RadialMenu();

	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onHackableOpen(cocos2d::EventCustom* eventArgs);
	void onHackableAttributeEdit(HackableAttribute* attribute);
	void onHackableAttributeEditDone();
	void close();
	void buildRadialMenu(HackableEvents::HackableObjectOpenArgs* args);
	cocos2d::Node* createRadialNode(std::string iconResource, cocos2d::Vec2 nodePosition, float angle, LocalizedString* text, std::function<void()> clickCallback);

	HackableObject* activeHackableObject;
	cocos2d::LayerColor* layerColor;
	cocos2d::Sprite* background;
	cocos2d::Node* radialMenuItems;
	std::function<void()> onRadialMenuCloseCallback;

	static const float Radius;
	static const float IconRadius;
};
