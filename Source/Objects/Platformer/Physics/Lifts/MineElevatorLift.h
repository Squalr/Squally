#pragma once

#include "Objects/Platformer/Physics/Lifts/LiftBase.h"

namespace cocos2d
{
	class Sprite;
}

class MineElevatorLift : public LiftBase
{
public:
	static MineElevatorLift* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineElevatorLift(cocos2d::ValueMap& properties);
	virtual ~MineElevatorLift();

	void onEnter() override;
	void initializePositions() override;
	float getPadding() override;
	cocos2d::Vec2 getRailsOffset() override;

private:
	typedef LiftBase super;

	cocos2d::Sprite* gearShaft;
	cocos2d::Sprite* gear;
	cocos2d::Sprite* elevator;
};
