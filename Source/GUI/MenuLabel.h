#pragma once
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class MenuLabel : public Node
{
public:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	MenuLabel(std::string labelText, std::string fontResource, float fontSize, std::function<void(MenuLabel*)> onMouseClick);
	~MenuLabel();

	bool Intersects(float mouseX, float mouseY);

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	void onEnter() override;

	Label* label;
	Label* labelHighlighted;

	std::function<void(MenuLabel*)> menuOnMouseClick;
};

