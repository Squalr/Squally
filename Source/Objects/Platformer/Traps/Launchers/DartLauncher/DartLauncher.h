#pragma once

#include "Objects/Platformer/Traps/Launchers/PivotLauncher.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class DartPool;
class HackableData;
class SmartAnimationNode;

class DartLauncher : public PivotLauncher
{
public:
	static DartLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DartLauncher(cocos2d::ValueMap& properties);
	virtual ~DartLauncher();

	void initializePositions() override;
	HackablePreview* createDefaultPreview() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* getTimerPreview() override;
	Projectile* createProjectile() override;

private:
	typedef PivotLauncher super;
};
