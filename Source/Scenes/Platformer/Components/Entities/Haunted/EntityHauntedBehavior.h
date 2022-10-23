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

	void runDialogue();

	static const std::string MapKey;
	static const std::string MapEventUnhaunted;
	static const std::string MapEventKeyOwnerId;

protected:
	EntityHauntedBehavior(GameObject* owner);
	virtual ~EntityHauntedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	bool tryUnhaunt();

	PlatformerEntity* entity = nullptr;
	cocos2d::Vec2 displayOffset;
	Inventory* inventory = nullptr;

	static const std::string PropertyLinkedEnemy;
	static const std::string SaveKeyUnhaunted;
};
