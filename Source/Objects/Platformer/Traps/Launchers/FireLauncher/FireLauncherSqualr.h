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

class FireLauncherSqualr : public PivotLauncher
{
public:
	static FireLauncherSqualr* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	FireLauncherSqualr(cocos2d::ValueMap& properties);
	virtual ~FireLauncherSqualr();

	void initializePositions() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
