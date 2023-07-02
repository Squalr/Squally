#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class DrawNode;
	class Sprite;
}

class ClickableNode;
class Inventory;
class PlatformerEntity;
class Portal;
class Sound;

class QuickSwap : public SmartNode
{
public:
	static QuickSwap* create();

protected:
	QuickSwap();
	virtual ~QuickSwap();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	PlatformerEntity* target = nullptr;
	ClickableNode* clickableNode = nullptr;
};
