#pragma once

#include "Entities/Isometric/IsometricEntity.h"

class IsometricSqually : public IsometricEntity
{
public:
	static IsometricSqually* deserialize(cocos2d::ValueMap& properties);
	static IsometricSqually* create(cocos2d::ValueMap& properties);

	static const std::string MapKeySqually;

protected:
	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef IsometricEntity super;
	IsometricSqually(cocos2d::ValueMap& properties);
	~IsometricSqually();

	void onEnter() override;
	void update(float) override;
};
