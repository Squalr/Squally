#pragma once

#include "Objects/Platformer/Breakables/BreakableCage.h"

namespace cocos2d
{
	class Sprite;
}

class CagedAnimal : public BreakableCage
{
public:

protected:
	CagedAnimal(cocos2d::ValueMap& initProperties, std::string saveKey);
	virtual ~CagedAnimal();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;

	cocos2d::Node* animalNode;

private:
	typedef BreakableCage super;

	cocos2d::Sprite* shineFx;
	std::string saveKey;
};
