#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class HelperInventoryRedirectBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
