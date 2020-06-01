#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class SmartParticles;

class GuanoUnpetrifyParticleBehavior : public AttachedBehavior
{
public:
	static GuanoUnpetrifyParticleBehavior* create(GameObject* owner);

	void unpetrify();

protected:
	GuanoUnpetrifyParticleBehavior(GameObject* owner);
	virtual ~GuanoUnpetrifyParticleBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	SmartParticles* unpetrifyParticles;
};
