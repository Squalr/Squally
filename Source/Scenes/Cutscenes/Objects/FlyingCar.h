#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;
class Smoke;

class FlyingCar : public SmartNode
{
public:
	enum CarType {
		Junker,
		Viper,
		Propeller
	};

	static FlyingCar* create(CarType carType, cocos2d::Vec2 speed, float groundHeight);

	void crash();

private:
	FlyingCar(CarType carType, cocos2d::Vec2 speed, float groundHeight);
	~FlyingCar();

	void explode();
	void onEnter() override;
	void update(float dt) override;

	float height;
	bool isCrashing;
	Smoke* smoke;
	SmartAnimationSequenceNode* carSprite;
	cocos2d::Vec2 flySpeed;

	static const std::string ScheduleKeySputterSmoke;
	static const float gravity;
};
