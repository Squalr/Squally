#pragma once

#include "Objects/Platformer/Traps/Launchers/PivotLauncher.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class HackableData;
class Projectile;
class SmartAnimationNode;

class WaterLauncher : public PivotLauncher
{
public:
	static WaterLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WaterLauncher(cocos2d::ValueMap& properties);
	virtual ~WaterLauncher();

	void initializePositions() override;
	cocos2d::Vec2 getProjectileSpawnPosition() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
