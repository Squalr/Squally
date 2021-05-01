#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class WorldSound;

class GuanoUnpetrifySoundBehavior : public Component
{
public:
	static GuanoUnpetrifySoundBehavior* create(GameObject* owner);

	void unpetrify();

protected:
	GuanoUnpetrifySoundBehavior(GameObject* owner);
	virtual ~GuanoUnpetrifySoundBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
	WorldSound* statueBreakSound;
};
