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
#include "Entities/Platformer/PlatformerEntity.h"
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

const std::string EntityHauntedBehavior::MapKey = "petrified";
const std::string EntityHauntedBehavior::SaveKeyUnhaunted = "SAVE_KEY_UNHAUNTED";
const std::string EntityHauntedBehavior::PropertyLinkedEnemy = "linked-enemy";
const std::string EntityHauntedBehavior::MapEventUnhaunted = "unhaunted";
const std::string EntityHauntedBehavior::MapEventKeyOwnerId = "owner-id";

EntityHauntedBehavior* EntityHauntedBehavior::create(GameObject* owner)
{
	EntityHauntedBehavior* instance = new EntityHauntedBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHauntedBehavior::EntityHauntedBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

EntityHauntedBehavior::~EntityHauntedBehavior()
{
}

void EntityHauntedBehavior::onLoad()
{
	if (this->entity->loadObjectStateOrDefault(EntityHauntedBehavior::SaveKeyUnhaunted, Value(false)).asBool())
	{
		this->toggleQueryable(true);

		return;
	}

	this->entity->watchForComponent<HexusBehaviorBase>([=](HexusBehaviorBase* hexusBehavior)
	{
		hexusBehavior->setVisible(false);
	});
	
	this->entity->getAnimations()->setVisible(false);
	this->toggleQueryable(true);
}

void EntityHauntedBehavior::onDisable()
{
	super::onDisable();
}

bool EntityHauntedBehavior::tryUnhaunt()
{
	if (this->inventory == nullptr)
	{
		return false;
	}

	Item* mirror = this->inventory->getItemOfType<MedusaMirror>();

	PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(mirror));

	this->entity->saveObjectState(EntityHauntedBehavior::SaveKeyUnhaunted, Value(true));

	if (this->entity->getEntityKey() == "elric")
	{
		QuestTask::SaveQuestSaveState(CureKingLine::MapKeyQuestLine, UnhauntCastle::MapKeyQuest, UnhauntCastle::SaveKeyElricCured, Value(true));
	}
	else if (this->entity->getEntityKey() == "leopold")
	{
		QuestTask::SaveQuestSaveState(CureKingLine::MapKeyQuestLine, UnhauntCastle::MapKeyQuest, UnhauntCastle::SaveKeyLeopoldCured, Value(true));
	}

	ValueMap args = ValueMap();

	args[EntityHauntedBehavior::MapEventKeyOwnerId] = this->entity->getUniqueIdentifier();

	this->entity->broadcastMapEvent(EntityHauntedBehavior::MapEventUnhaunted, args);

	return true;
}

void EntityHauntedBehavior::runDialogue()
{
	this->entity->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* dialogueBehavior)
	{
		if (this->entity->getEntityKey() == "ajax")
		{
			dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_TODO::create(), Voices::GetNextVoiceShort());
		}
		else if (this->entity->getEntityKey() == "griffin")
		{
			dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_TODO::create(), Voices::GetNextVoiceShort());
		}
		else if (this->entity->getEntityKey() == "geryon")
		{
			dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_TODO::create(), Voices::GetNextVoiceMedium());
		}
		else if (this->entity->getEntityKey() == "athena")
		{
			dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_TODO::create(), Voices::GetNextVoiceShort());
		}
		else
		{
			dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_TODO::create(), Voices::GetNextVoiceShort());
		}

		int cureCount = QuestTask::GetQuestSaveStateOrDefault(CureKingLine::MapKeyQuestLine, UnhauntCastle::MapKeyQuest, UnhauntCastle::SaveKeyUnhauntedCount, Value(0)).asInt() + 1;

		if (cureCount >= UnhauntCastle::MaxCuredCount)
		{
			Objectives::SetCurrentObjective(ObjectiveKeys::URReturnToHera);
		}

		QuestTask::SaveQuestSaveState(CureKingLine::MapKeyQuestLine, UnhauntCastle::MapKeyQuest, UnhauntCastle::SaveKeyUnhauntedCount, Value(cureCount));
	});
}
