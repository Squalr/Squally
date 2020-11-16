#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class VictoryMenu : public SmartNode
{
public:
	static VictoryMenu* create();

protected:
	VictoryMenu();
	virtual ~VictoryMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* segfaultMenu;
	LocalizedLabel* titleLabel;
	ClickableTextNode* leaveButton;
};
