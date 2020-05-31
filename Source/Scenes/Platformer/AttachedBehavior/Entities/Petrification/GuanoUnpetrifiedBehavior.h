#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class SmartParticles;
class WorldSound;

class GuanoUnpetrifiedBehavior : public AttachedBehavior
{
public:
	static GuanoUnpetrifiedBehavior* create(GameObject* owner);

	void unpetrify();

protected:
	GuanoUnpetrifiedBehavior(GameObject* owner);
	virtual ~GuanoUnpetrifiedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	SmartParticles* unpetrifyParticles;
	WorldSound* statueBreakSound;
};
