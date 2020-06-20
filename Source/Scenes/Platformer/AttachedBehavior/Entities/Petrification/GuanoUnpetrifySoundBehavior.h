#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class WorldSound;

class GuanoUnpetrifySoundBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	WorldSound* statueBreakSound;
};
