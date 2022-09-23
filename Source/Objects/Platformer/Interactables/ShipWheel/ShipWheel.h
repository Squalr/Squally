#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class ShipWheel : public InteractObject
{
public:
	static ShipWheel* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ShipWheel(cocos2d::ValueMap& properties);
	virtual ~ShipWheel();

	void initializePositions() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	void showCharterShipOptions();
	void steeringWheelWarp(std::string mapFile);

	cocos2d::Sprite* neck = nullptr;
	cocos2d::Sprite* wheel = nullptr;
};
