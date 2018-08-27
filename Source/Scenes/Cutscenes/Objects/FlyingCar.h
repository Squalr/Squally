#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class FlyingCar : public Node
{
public:
	enum CarType {
		Junker,
		Viper,
		Propeller
	};

	static FlyingCar* create(CarType carType, Vec2 speed);

private:
	FlyingCar(CarType carType, Vec2 speed);
	~FlyingCar();

	void onEnter() override;
	void update(float dt) override;

	Sprite* carSprite;
	Vec2 flySpeed;
};
