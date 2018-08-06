#pragma once
#include "cocos2d.h"

#include "Entities/Isometric/IsometricEntity.h"
#include "Resources.h"

using namespace cocos2d;

class Shiftman : public IsometricEntity
{
public:
	static Shiftman * deserialize(ValueMap* initProperties);

	static const std::string KeyShiftmanProperty;

private:
	Shiftman(ValueMap* initProperties);
	~Shiftman();

	void registerHackables();
	void onEnter() override;
	void update(float) override;
};
