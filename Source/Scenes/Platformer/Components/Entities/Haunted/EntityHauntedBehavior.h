#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class PlatformerEnemy;
class PlatformerFriendly;

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

	PlatformerEnemy* ownerAsEnemy = nullptr;
	PlatformerFriendly* ownerAsFriendly = nullptr;
	bool isOtherWorld = false;
	std::string hauntedKey;

	static const std::string PropertyOtherWorld;
	static const std::string PropertyHauntedKey;
};
