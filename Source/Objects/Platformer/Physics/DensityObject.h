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

	float currentDensity = 0.0f;
	float loadedDensity = 0.0f;

	cocos2d::Node* contentNode = nullptr;

private:
	typedef HackableObject super;
	friend class BinderDensityObject;
	
	float heightRange = 0.0f;

	static const float DensityFloatSpeed;
};
