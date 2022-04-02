#pragma once

#include "Engine/Hackables/HackableObject.h"

class SmartAnimationNode;

class Airship : public HackableObject
{
public:
	static Airship* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Airship(cocos2d::ValueMap& properties);
	virtual ~Airship();

	void onEnter() override;
	void update(float dt) override;

private:
	typedef HackableObject super;

	SmartAnimationNode* animations = nullptr;
	float speed = 320.0f;

	static const std::string PropertyVariant;
	static const std::string PropertySpeed;
};
