#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class MenuLabel : public Node
{
public:
	static MenuLabel * create(std::string labelText, std::string fontResource, float fontSize);

	void setText(std::string text);
	void setColor(Color4B color);
	void setHoverColor(Color4B color);
	void setGlowColor(Color4B color);
	void setCallback(std::function<void(MenuLabel*)> callback);

protected:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	~MenuLabel();

private:
	void onEnter() override;
	void initializeListeners();
	void onMouseMove(EventMouse* event);
	void onMouseDown(EventMouse* event);

	Label* label;
	Label* labelHighlighted;
	std::function<void(MenuLabel*)> menuOnMouseClick;

	Color4B normalColor = Color4B::WHITE;
	Color4B hoverColor = Color4B(0x6c, 0xa5, 0xad, 0xff);
	Color4B glowColor = Color4B(255, 255, 168, 255);

	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};
