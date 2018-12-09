#pragma once
#include <functional>
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventMouse;
	class Label;
}

class MenuLabel : public SmartNode
{
public:
	static MenuLabel * create(std::string labelText, std::string fontResource, float fontSize);

	void setText(std::string text);
	void setColor(cocos2d::Color4B color);
	void setHoverColor(cocos2d::Color4B color);
	void setGlowColor(cocos2d::Color4B color);
	void setCallback(std::function<void(MenuLabel*)> callback);

protected:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	virtual ~MenuLabel();

private:
	void onEnter() override;
	void initializeListeners();
	void onMouseMove(cocos2d::EventMouse* event);
	void onMouseDown(cocos2d::EventMouse* event);

	cocos2d::Label* label;
	cocos2d::Label* labelHighlighted;
	std::function<void(MenuLabel*)> menuOnMouseClick;

	cocos2d::Color4B normalColor = cocos2d::Color4B::WHITE;
	cocos2d::Color4B hoverColor = cocos2d::Color4B(0x6c, 0xa5, 0xad, 0xff);
	cocos2d::Color4B glowColor = cocos2d::Color4B(255, 255, 168, 255);

	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};
