#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class Inventory;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

class EntityHauntedBehavior : public GameComponent
{
public:
	static EntityHauntedBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityHauntedBehavior(GameObject* owner);
	virtual ~EntityHauntedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
