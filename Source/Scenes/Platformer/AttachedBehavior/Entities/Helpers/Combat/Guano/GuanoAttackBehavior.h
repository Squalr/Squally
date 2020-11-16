#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class GuanoAttackBehavior : public AttachedBehavior
{
public:
	static GuanoAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoAttackBehavior(GameObject* owner);
	virtual ~GuanoAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
