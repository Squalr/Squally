#pragma once
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Node;
}

class FocusTakeOver : public SmartNode
{
public:
	static FocusTakeOver * create();

	void focus(std::vector<cocos2d::Node*> nodes);
	void unfocus(bool fadeOut = true);

private:
	typedef SmartNode super;
	FocusTakeOver();
	virtual ~FocusTakeOver();

	void onEnter() override;
	void initializeListeners() override;
	void beforeSceneChange();

	cocos2d::LayerColor* focusBackground;
	std::map<cocos2d::Node*, std::tuple<cocos2d::Node*, int>> hijackedNodes;
};
