#pragma once
#include "cocos/math/Vec2.h"

#include "Engine/Hackables/HackableObject.h"

class HackableData;

class PendulumBlade : public HackableObject
{
public:
	static PendulumBlade* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPendulumBlade;

protected:
	PendulumBlade(cocos2d::ValueMap* initProperties);
	~PendulumBlade();

	cocos2d::Vec2 getButtonOffset() override;

private:
	void registerHackables();
	void onEnter() override;
	void update(float) override;
	void buildChain();

	cocos2d::Node* bladeChain;
	float chainHeight;

	HackableData* pendulumBladeDataSpeedY;
	cocos2d::Vec2 pendulumBladeSpeed;
};
