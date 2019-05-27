#pragma once
#include <vector>

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
	class Node;
}

class FocusTakeOver : public Hud
{
public:
	static FocusTakeOver* create();

	void focus(std::vector<cocos2d::Node*> nodes);
	void unfocus(bool fadeOut = true);

private:
	typedef Hud super;
	FocusTakeOver();
	virtual ~FocusTakeOver();

	void onEnter() override;
	void initializeListeners() override;

	cocos2d::LayerColor* focusBackground;
	std::map<cocos2d::Node*, std::tuple<cocos2d::Node*, int>> hijackedNodes;
};
