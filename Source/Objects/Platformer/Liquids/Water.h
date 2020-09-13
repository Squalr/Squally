#pragma once
#include <set>

#include "Engine/Physics/Liquid/LiquidNode.h"

namespace cocos2d
{
	class ParticleSystem;
}

class HackableData;

class Water : public LiquidNode
{
public:
	static Water* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Water(cocos2d::ValueMap& properties);
	virtual ~Water();
	
	void initializeListeners() override;
	void applyWaterForce(CollisionObject* target, float dt);

private:
	typedef LiquidNode super;

	static const cocos2d::Color4B SurfaceColor;
	static const cocos2d::Color4B BodyColor;
};
