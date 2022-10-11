#pragma once

#include "Objects/Platformer/Physics/Lifts/LiftBase.h"

namespace cocos2d
{
	class Sprite;
}

class CartLift : public LiftBase
{
public:
	static CartLift* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CartLift(cocos2d::ValueMap& properties);
	virtual ~CartLift();

	void initializePositions() override;
	float getPadding() override;

private:
	typedef LiftBase super;

	cocos2d::Sprite* platform = nullptr;
	cocos2d::Sprite* endStop = nullptr;
	cocos2d::Sprite* startStop = nullptr;
};
