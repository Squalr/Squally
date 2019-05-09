#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class PlatformerEntity;
class ScrollPane;

class VictoryMenu : public SmartNode
{
public:
	static VictoryMenu* create();

private:
	typedef SmartNode super;
	VictoryMenu();
	virtual ~VictoryMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* segfaultMenu;
	LocalizedLabel* titleLabel;
	ClickableTextNode* leaveButton;
};
