#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class HelperInventoryRedirectBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
