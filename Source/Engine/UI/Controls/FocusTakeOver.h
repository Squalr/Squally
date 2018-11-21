#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class FocusTakeOver : public SmartNode
{
public:
	static FocusTakeOver * create();

	void focus(std::vector<Node*> nodes);
	void unfocus(bool fadeOut = true);

private:
	FocusTakeOver();
	~FocusTakeOver();

	void onEnter() override;
	void initializeListeners() override;
	void beforeSceneChange();

	LayerColor* focusBackground;
	std::map<Node*, std::tuple<Node*, int>> hijackedNodes;
};
