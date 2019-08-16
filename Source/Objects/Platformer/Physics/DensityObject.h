#pragma once

#include "Engine/Hackables/HackableObject.h"

class DensityObject : public HackableObject
{
public:
	static const std::string MapKeyDensity;

protected:
	DensityObject(cocos2d::ValueMap& properties);
	virtual ~DensityObject();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	virtual float getDensity() = 0;
	virtual float getObjectHeight() = 0;

	float currentDensity;
	float loadedDensity;

	cocos2d::Node* contentNode;

private:
	typedef HackableObject super;

	float heightRange;

	static const float DensityFloatSpeed;
};
