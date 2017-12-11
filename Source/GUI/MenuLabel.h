#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MenuLabel : public Node
{
public:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	MenuLabel(std::string labelText, std::string fontResource, float fontSize, std::function<void(MenuLabel*)> onMouseClick);
	~MenuLabel();

	Size GetSize();
	bool Intersects(float mouseX, float mouseY);

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	void onEnter() override;

	Label* label;
	Label* labelHighlighted;
	std::function<void(MenuLabel*)> menuOnMouseClick;

	const Color4B* highlightColor = new Color4B(255, 255, 168, 255);
	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};

