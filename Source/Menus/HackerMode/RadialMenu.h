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
}

class ClickableNode;
class CodeEditor;
class HackableCode;
class HackableData;
class HackableObject;

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
	void onHackableEdit(cocos2d::EventCustom* eventArgs);
	void onHackableCodeClick(HackableCode* hackableCode);
	void onHackableDataClick(HackableData* hackableData);
	void close();
	void buildRadialMenu(HackableEvents::HackableObjectEditArgs* args);
	cocos2d::Node* createRadialNode(std::string iconResource, cocos2d::Vec2 nodePosition, cocos2d::Color4F color, bool drawLine, std::function<void()> clickCallback);

	CodeEditor* codeEditor;
	HackableObject* activeHackableObject;
	cocos2d::LayerColor* layerColor;
	cocos2d::Node* radialMenuItems;
	std::function<void()> onRadialMenuCloseCallback;

	static const float DataRadius;
	static const float CodeRadius;
	static const float LineWidth;
	static const cocos2d::Color4F DataColorFill;
	static const cocos2d::Color4F CodeColorFill;
	static const cocos2d::Color4F DataColor;
	static const cocos2d::Color4F CodeColor;
	static const float IconRadius;
};
