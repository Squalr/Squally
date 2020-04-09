#pragma once

#include "Entities/Isometric/PointerTrace/GridEntity.h"

class IsometricBall : public GridEntity
{
public:
	static IsometricBall* deserialize(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IsometricBall(cocos2d::ValueMap& properties);
	virtual ~IsometricBall();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;

private:
	typedef GridEntity super;

	static const float MovementSpeed;
};
