#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class SmartParticles;

class GuanoUnpetrifyParticleBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	SmartParticles* unpetrifyParticles = nullptr;
};
