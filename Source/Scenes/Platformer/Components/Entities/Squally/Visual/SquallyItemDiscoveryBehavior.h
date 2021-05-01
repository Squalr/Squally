#pragma once

#include "Engine/Components/Component.h"

namespace cocos2d
{
	class Sprite;
};

class Item;
class Squally;
class Sound;

class SquallyItemDiscoveryBehavior : public Component
{
public:
	static SquallyItemDiscoveryBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyItemDiscoveryBehavior(GameObject* owner);
	virtual ~SquallyItemDiscoveryBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void discoverItem(Item* item, bool cinematicHijack);

	cocos2d::Node* container;
	cocos2d::Node* itemNode;
	cocos2d::Sprite* glow;
	Sound* discoverSound;

	Squally* squally;
};
