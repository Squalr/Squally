#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationNode;

class Computer : public InteractObject
{
public:
	static Computer* create(cocos2d::ValueMap& properties);

	void turnOn();
	void turnOff();

	static const std::string MapKey;

protected:
	Computer(cocos2d::ValueMap& properties);
	virtual ~Computer();

	void onEnter() override;
	void initializePositions() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	SmartAnimationNode* animations = nullptr;

	static const std::string PropertyComputerType;
};
