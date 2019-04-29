#pragma once

#include "Entities/Isometric/IsometricEntity.h"

class IsometricBall : public IsometricEntity
{
public:
	static IsometricBall* deserialize(cocos2d::ValueMap& initProperties);
	static IsometricBall* create(cocos2d::ValueMap& initProperties);

	static const std::string KeyBallProperty;

protected:
	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef IsometricEntity super;
	IsometricBall(cocos2d::ValueMap& initProperties);
	~IsometricBall();

	void onEnter() override;
	void update(float) override;

	static IsometricBall* instance;
};
