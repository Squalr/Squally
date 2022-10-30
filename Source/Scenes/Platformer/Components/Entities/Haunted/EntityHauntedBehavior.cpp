#include "EntityHauntedBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/CureKingLine.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EntityHauntedBehavior::MapKey = "haunted";
const std::string EntityHauntedBehavior::PropertyOtherWorld = "other-world";
const std::string EntityHauntedBehavior::PropertyHauntedKey = "haunted-key";

EntityHauntedBehavior* EntityHauntedBehavior::create(GameObject* owner)
{
	EntityHauntedBehavior* instance = new EntityHauntedBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHauntedBehavior::EntityHauntedBehavior(GameObject* owner) : super(owner)
{
	this->ownerAsEnemy = dynamic_cast<PlatformerEnemy*>(owner);
	this->ownerAsFriendly = dynamic_cast<PlatformerFriendly*>(owner);

	if (this->ownerAsEnemy == nullptr && this->ownerAsFriendly == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->isOtherWorld = GameUtils::getKeyOrDefault(this->owner->properties, EntityHauntedBehavior::PropertyOtherWorld, Value(false)).asBool();
		this->hauntedKey = GameUtils::getKeyOrDefault(this->owner->properties, EntityHauntedBehavior::PropertyHauntedKey, Value("")).asString();
	}
}

EntityHauntedBehavior::~EntityHauntedBehavior()
{
}

void EntityHauntedBehavior::onLoad()
{
	if (this->ownerAsFriendly != nullptr)
	{
		if (this->isOtherWorld)
		{
			this->ownerAsFriendly->getAnimations()->setOpacity(127);
		}

		this->ownerAsFriendly->setState(StateKeys::PatrolHijacked, Value(true));

		// Defer 1 frame to give the dead enemy a chance to persist the save key
		this->defer([=]()
		{
			if (!SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool())
			{
				this->ownerAsFriendly->getAnimations()->playAnimation("Cower", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
			}
		});
	}
	else if (this->ownerAsEnemy != nullptr)
	{
		if (this->isOtherWorld)
		{
			this->ownerAsEnemy->getAnimations()->setOpacity(127);
		}

		if (!this->ownerAsEnemy->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			if (!SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool())
			{
				SaveManager::SoftSaveProfileData(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(true));

				int unhauntedCount = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt();
				SaveManager::SoftSaveProfileData(UnhauntCastle::SaveKeyUnhauntedCount, Value(unhauntedCount + 1));
			}
		}
	}
}

void EntityHauntedBehavior::onDisable()
{
	super::onDisable();
}
