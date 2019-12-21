#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class ShopkeeperDialogueBehavior : public AttachedBehavior
{
public:
	static ShopkeeperDialogueBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ShopkeeperDialogueBehavior(GameObject* owner);
	~ShopkeeperDialogueBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
};
