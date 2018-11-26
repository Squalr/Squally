#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Scenes/Cutscenes/Objects/Explosion.h"
#include "Scenes/Cutscenes/Objects/Smoke.h"
#include "Resources/CutsceneResources.h"

using namespace cocos2d;

class FlyingCar : public Node
{
public:
	enum CarType {
		Junker,
		Viper,
		Propeller
	};

	static FlyingCar* create(CarType carType, Vec2 speed, float groundHeight);

	void crash();

private:
	FlyingCar(CarType carType, Vec2 speed, float groundHeight);
	~FlyingCar();

	void explode();

	void onEnter() override;
	void update(float dt) override;

	float height;
	bool isCrashing;
	Smoke* smoke;
	Sprite* carSprite;
	Vec2 flySpeed;

	static const std::string ScheduleKeySputterSmoke;
	static const float gravity;
};
