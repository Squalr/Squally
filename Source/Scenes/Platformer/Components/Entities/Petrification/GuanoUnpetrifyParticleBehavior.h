#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class SmartParticles;

class GuanoUnpetrifyParticleBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	SmartParticles* unpetrifyParticles;
};
