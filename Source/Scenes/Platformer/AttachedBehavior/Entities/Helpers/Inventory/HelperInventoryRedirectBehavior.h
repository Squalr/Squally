#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class HelperInventoryRedirectBehavior : public AttachedBehavior
{
public:
	static HelperInventoryRedirectBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HelperInventoryRedirectBehavior(GameObject* owner);
	virtual ~HelperInventoryRedirectBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
