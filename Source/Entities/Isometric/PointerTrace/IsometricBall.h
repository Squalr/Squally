#pragma once

#include "Entities/Isometric/PointerTrace/GridEntity.h"

class IsometricBall : public GridEntity
{
public:
	static IsometricBall* deserialize(cocos2d::ValueMap& properties);

	static const std::string MapKeyBall;

private:
	typedef GridEntity super;
	IsometricBall(cocos2d::ValueMap& properties);
	~IsometricBall();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;

	static const float MovementSpeed;
};
