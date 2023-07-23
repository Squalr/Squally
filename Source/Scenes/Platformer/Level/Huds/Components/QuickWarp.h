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

class QuickWarp : public SmartNode
{
public:
	static QuickWarp* create();

protected:
	QuickWarp();
	virtual ~QuickWarp();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	Portal* internalPortal = nullptr;
	PlatformerEntity* target = nullptr;
	ClickableNode* clickableNode = nullptr;
};
