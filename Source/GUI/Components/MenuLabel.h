#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MenuLabel : public Node
{
public:
	static MenuLabel * create(std::string labelText, std::string fontResource, float fontSize);

	void SetCallback(std::function<void(MenuLabel*)> callback);

protected:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	~MenuLabel();

	void SetText(std::string text);

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	Label* label;
	Label* labelHighlighted;
	std::function<void(MenuLabel*)> menuOnMouseClick;

	const Color4B* highlightColor = new Color4B(255, 255, 168, 255);
	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};

