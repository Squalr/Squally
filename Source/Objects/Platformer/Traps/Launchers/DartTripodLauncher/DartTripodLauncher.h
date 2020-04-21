#pragma once

#include "Objects/Platformer/Traps/Launchers/PivotLauncher.h"

class AnimationPart;
class HackableData;
class SmartAnimationNode;

class DartTripodLauncher : public PivotLauncher
{
public:
	static DartTripodLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DartTripodLauncher(cocos2d::ValueMap& properties);
	virtual ~DartTripodLauncher();

	void initializePositions() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* getTimerPreview() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
