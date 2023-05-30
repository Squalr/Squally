#pragma once

#include "Objects/Platformer/Interactables/ToggleableObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;
class WorldSound;

class Switch : public ToggleableObject
{
public:
	static Switch* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Switch(cocos2d::ValueMap& properties);
	virtual ~Switch();

	void onEnter() override;
	void initializePositions() override;
	void onToggle(bool isInstant = true) override;
	void onEnable(bool isInit, bool isInstant = true) override;
	void onDisable(bool isInit, bool isInstant = true) override;

private:
	typedef ToggleableObject super;

	cocos2d::Sprite* switchOn = nullptr;
	cocos2d::Sprite* switchOff = nullptr;
	WorldSound* interactSound = nullptr;
};
