#pragma once

#include "Objects/Platformer/Traps/Launchers/PivotLauncher.h"

class Projectile;

class DartTripodLauncherSqualr : public PivotLauncher
{
public:
	static DartTripodLauncherSqualr* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DartTripodLauncherSqualr(cocos2d::ValueMap& properties);
	virtual ~DartTripodLauncherSqualr();

	void initializePositions() override;
	cocos2d::Vec2 getProjectileSpawnPosition() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
