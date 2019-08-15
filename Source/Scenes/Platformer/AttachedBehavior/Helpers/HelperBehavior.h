#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class HelperBehavior : public AttachedBehavior
{
public:
	static HelperBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	HelperBehavior(GameObject* owner);
	~HelperBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	bool isOnGround();

	PlatformerEntity* entity;
};
