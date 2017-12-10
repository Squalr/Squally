#pragma once
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class MenuLabel : public Node
{
public:
	MenuLabel(std::string labelText, std::string fontResource, float fontSize);
	~MenuLabel();

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	void onEnter() override;

	Label* label;
	Label* labelHighlighted;
};

