#pragma once

#include "Engine/Hackables/HackableObject.h"

class SmartAnimationNode;

class Airship2 : public HackableObject
{
public:
	static Airship2* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyAirship2;

protected:
	Airship2(cocos2d::ValueMap& properties);
	virtual ~Airship2();

	void onEnter() override;
	void update(float dt) override;

private:
	typedef HackableObject super;

	SmartAnimationNode* animations;
};
