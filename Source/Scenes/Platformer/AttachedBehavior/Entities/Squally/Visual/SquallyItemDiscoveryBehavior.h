#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
};

class Item;
class Squally;
class SmartAnimationSequenceNode;
class Sound;

class SquallyItemDiscoveryBehavior : public AttachedBehavior
{
public:
	static SquallyItemDiscoveryBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyItemDiscoveryBehavior(GameObject* owner);
	virtual ~SquallyItemDiscoveryBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void discoverItem(Item* item);

	cocos2d::Node* container;
	cocos2d::Node* itemNode;
	cocos2d::Sprite* glow;
	Sound* discoverSound;

	Squally* squally;
};
