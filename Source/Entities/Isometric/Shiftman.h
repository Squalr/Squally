#pragma once

#include "Entities/Isometric/IsometricEntity.h"

class Shiftman : public IsometricEntity
{
public:
	static Shiftman* deserialize(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Shiftman(cocos2d::ValueMap& properties);
	virtual ~Shiftman();

	void onEnter() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef IsometricEntity super;
};
