#pragma once
#include "cocos/math/Vec2.h"

#include "Engine/Hackables/HackableObject.h"

class HackableData;

namespace cocos2d
{
	class Sprite;
}

class MechanicalFlail : public HackableObject
{
public:
	static MechanicalFlail* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMechanicalFlail;

protected:
	MechanicalFlail(cocos2d::ValueMap* initProperties);
	~MechanicalFlail();

	cocos2d::Vec2 getButtonOffset() override;

private:
	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void buildChain();

	cocos2d::Sprite* joint;
	cocos2d::Node* flailChain;
	float flailHeight;

	HackableData* pendulumBladeDataSpeedY;
	cocos2d::Vec2 pendulumBladeSpeed;
};
