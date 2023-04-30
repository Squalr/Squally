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
class Sound;

class QuickPotion : public SmartNode
{
public:
	static QuickPotion* create();

	void setInventory(Inventory* inventory);

protected:
	QuickPotion();
	virtual ~QuickPotion();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	Inventory* inventory = nullptr;
	PlatformerEntity* target = nullptr;
	ClickableNode* clickableNode = nullptr;
};
