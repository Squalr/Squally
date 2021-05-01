#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Squally;

class ShopkeeperDialogueBehavior : public Component
{
public:
	static ShopkeeperDialogueBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShopkeeperDialogueBehavior(GameObject* owner);
	virtual ~ShopkeeperDialogueBehavior();

	void onLoad() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
	Squally* squally;
};
