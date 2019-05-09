#pragma once

#include "Entities/Isometric/PointerTrace/GridEntity.h"

class IsometricBall : public GridEntity
{
public:
	static IsometricBall* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string KeyBallProperty;

private:
	typedef GridEntity super;
	IsometricBall(cocos2d::ValueMap& initProperties);
	~IsometricBall();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;

	static const float MovementSpeed;
};
