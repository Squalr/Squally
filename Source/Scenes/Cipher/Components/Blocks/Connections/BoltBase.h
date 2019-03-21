#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class BoltBase : public SmartNode
{
public:

protected:
	BoltBase();
	~BoltBase();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	ClickableNode* connectButton;
};
