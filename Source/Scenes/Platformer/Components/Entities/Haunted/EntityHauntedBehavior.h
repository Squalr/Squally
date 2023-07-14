#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class LocalizedString;
class PlatformerEnemy;
class PlatformerFriendly;

class EntityHauntedBehavior : public GameComponent
{
public:
	static EntityHauntedBehavior* create(GameObject* owner);

	bool isUnhaunted() const;
	void onSoulHarvested();

	static const std::string MapKey;
	static const std::string PropertyOtherWorld;
	static const std::string PropertyHauntedKey;

protected:
	EntityHauntedBehavior(GameObject* owner);
	virtual ~EntityHauntedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void unhaunt();
	LocalizedString* getNextSpeechBubbleText();
	
	PlatformerEnemy* ownerAsEnemy = nullptr;
	PlatformerFriendly* ownerAsFriendly = nullptr;
	bool isOtherWorld = false;
	std::string hauntedKey;
};
