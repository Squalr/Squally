#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class FocusTakeOver : public Node
{
public:
	static FocusTakeOver * create();

	void showPointer(Vec2 coords, float rotation);
	void focus(std::vector<Node*> nodes);
	void unfocus(bool fadeOut = true);

private:
	FocusTakeOver();
	~FocusTakeOver();

	LayerColor* focusBackground;
	std::map<Node*, std::tuple<Node*, int>> hijackedNodes;
};
