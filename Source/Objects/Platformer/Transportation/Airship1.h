#pragma once

#include "Engine/Hackables/HackableObject.h"

class SmartAnimationNode;

class Airship1 : public HackableObject
{
public:
	static Airship1* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Airship1(cocos2d::ValueMap& properties);
	virtual ~Airship1();

	void onEnter() override;
	void update(float dt) override;

private:
	typedef HackableObject super;

	SmartAnimationNode* animations;
};
