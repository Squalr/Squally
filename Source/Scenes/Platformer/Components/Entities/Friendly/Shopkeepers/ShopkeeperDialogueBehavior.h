#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Squally;

class ShopkeeperDialogueBehavior : public GameComponent
{
public:
	static ShopkeeperDialogueBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShopkeeperDialogueBehavior(GameObject* owner);
	virtual ~ShopkeeperDialogueBehavior();

	void onLoad() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
	Squally* squally;
};
