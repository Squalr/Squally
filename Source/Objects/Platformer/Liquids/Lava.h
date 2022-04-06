#pragma once
#include <set>

#include "Engine/Physics/Liquid/LiquidNode.h"

class Lava : public LiquidNode
{
public:
	static Lava* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Lava(cocos2d::ValueMap& properties);
	virtual ~Lava();
	
	void initializeListeners() override;
	void applyLavaForce(CollisionObject* target, float dt);

private:
	typedef LiquidNode super;

	static const cocos2d::Color4B SurfaceColor;
	static const cocos2d::Color4B BodyColor;
	static const float LavaGravity;
};
