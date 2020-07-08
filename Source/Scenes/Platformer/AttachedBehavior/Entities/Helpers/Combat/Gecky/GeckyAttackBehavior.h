#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class GeckyAttackBehavior : public AttachedBehavior
{
public:
	static GeckyAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyAttackBehavior(GameObject* owner);
	virtual ~GeckyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
