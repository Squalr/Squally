#pragma once
#include <functional>
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventMouse;
}

class LocalizedLabel;

class MenuLabel : public SmartNode
{
public:
	static MenuLabel* create(LocalizedLabel* label);

	void setColor(cocos2d::Color4B color);
	void setHoverColor(cocos2d::Color4B color);
	void setGlowColor(cocos2d::Color4B color);
	void setCallback(std::function<void(MenuLabel*)> callback);

protected:
	MenuLabel(LocalizedLabel* label);
	virtual ~MenuLabel();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializeListeners();
	void onMouseMove(cocos2d::EventMouse* event);
	void onMouseDown(cocos2d::EventMouse* event);

	LocalizedLabel* label;
	LocalizedLabel* labelHighlighted;
	std::function<void(MenuLabel*)> menuOnMouseClick;

	cocos2d::Color4B normalColor = cocos2d::Color4B::WHITE;
	cocos2d::Color4B hoverColor = cocos2d::Color4B(0x6c, 0xa5, 0xad, 0xff);
	cocos2d::Color4B glowColor = cocos2d::Color4B(255, 255, 168, 255);

	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};
