#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class OutlineLabel : public Node
{
public:
	static OutlineLabel * create(std::string labelText, std::string fontResource, float fontSize);

	void setText(std::string text);
	void setColor(Color3B color);

private:
	OutlineLabel(std::string labelText, std::string fontResource, float fontSize);
	~OutlineLabel();

	Label * label;
	Label* labelHighlighted;

	const Color4B* highlightColor = new Color4B(255, 255, 168, 255);
	const float fontOutlineSize = 2.0f;
	const float highlightOutlineSize = 4.0f;
};
