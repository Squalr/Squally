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

class FireLauncher : public PivotLauncher
{
public:
	static FireLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	FireLauncher(cocos2d::ValueMap& properties);
	virtual ~FireLauncher();

	void initializePositions() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
